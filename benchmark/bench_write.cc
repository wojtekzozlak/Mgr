#include <time.h>

#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <boost/timer/timer.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <iomanip>
#include <vector>

#include <supersonic/base/infrastructure/tuple_schema.h>
#include <supersonic/base/memory/memory.h>
#include <supersonic/cursor/infrastructure/table.h>
#include <supersonic/cursor/infrastructure/view_printer.h>
#include <supersonic/contrib/storage/base/raw_storage.h>
#include <supersonic/contrib/storage/core/file_storage.h>
#include <supersonic/contrib/storage/core/file_series.h>
#include <supersonic/contrib/storage/core/storage_sink.h>
#include <supersonic/contrib/storage/util/path_util.h>
#include <supersonic/utils/file.h>

#include "src/schema.h"
#include "src/benchmarking_file.h"

const double BYTES_IN_MEG = 1024.0 * 1024.0;

void flush_cache() {
  std::cerr << "Flushing system cache" << std::endl;
  system("echo 3 > /proc/sys/vm/drop_caches");
}

int create_value(const supersonic::Attribute& attr,
    supersonic::TableRowWriter& writer, std::string& value) {
  std::stringstream reader(value);
  switch (attr.type()) {
    case supersonic::INT32:
      int i;
      reader >> i;
      writer.Int32(i);
      return sizeof(int32_t);
    case supersonic::FLOAT:
      float f;
      reader >> f;
      writer.Float(f);
      return sizeof(float);
    case supersonic::DATE:
      struct tm time;
      strptime(value.c_str(), "%Y-%m-%d", &time);
      writer.Date(mktime(&time) / 86400);
      return sizeof(int32_t);
    case supersonic::STRING:
      writer.String(value);
      return value.size();
    default:
      throw "Unknown type.";
  }
}

long parse_line(const std::string& line, supersonic::TupleSchema& schema,
    supersonic::TableRowWriter& writer) {
  std::vector<std::string> pieces;
  boost::split(pieces, line, boost::is_any_of("|"), boost::token_compress_on);

  writer.AddRow();
  long size = 0;
  for (int i = 0; i < schema.attribute_count(); i++) {
    size += create_value(schema.attribute(i), writer, pieces[i]);
  }
  return size;
}

#define CHECK_FAILURE(x) {\
  if (x.is_failure()) { \
    std::cerr << x.exception().ToString();\
    exit(1);\
  }\
}

int main(int argc, const char* argv[]) {
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " FILENAME OUTPUT_DIR" << std::endl;
    return 1;
  }

  const char* filename = argv[1];
  const std::string out_dir(argv[2]);
  std::cerr << "Opening file '" << filename << "'" << std::endl;
  std::ifstream file(filename);

  supersonic::TupleSchema tuple_schema = lineitem_schema();
  supersonic::ViewPrinter printer;
  supersonic::BufferAllocator* allocator =
      supersonic::HeapBufferAllocator::Get();

  std::cerr << "Loading data into memory..." << std::endl;

  std::string line;
  supersonic::Table table(tuple_schema, allocator);
  supersonic::TableRowWriter writer(&table);
  long data_size = 0;
  long rows = 0;
  while (std::getline(file, line)) {
    data_size += parse_line(line, tuple_schema, writer);
    rows++;
    if (rows % 100000 == 0) {
      std::cerr << "Loaded " << rows << " (" << data_size / BYTES_IN_MEG << "MB) " << std::endl;
    }
  }
  std::cerr << "Loaded. Flushing into storage." << std::endl;

  //static const int batches_arr[] = {100, 200, 500, 1000, 2000, 3000, 4000, 5000};
  static const int batches_arr[] = {5000, 4000, 3000, 2000, 1000, 500, 200, 100};
  //static const int batches_arr[] = {4000, 5000};
  std::vector<int> batches(batches_arr, batches_arr + sizeof(batches_arr) / sizeof(batches_arr[0]));
  //static const int families_arr[] = {1, 2, 4, 8, 16};
  static const int families_arr[] = {1, 2, 4, 8, 16};
  std::vector<int> families(families_arr, families_arr + sizeof(families_arr) / sizeof(families_arr[0]));

  int repeat = 3;
  for (int i = 0; i < repeat; i++) {
  for (int batch_size : batches) {
  for (int family_size : families) {

  bool repeat;
  do {
    repeat = false;
    flush_cache();
    std::stringstream ss("");
    ss << out_dir << "/" << batch_size << "_" << family_size;
    std::string out = ss.str();
    std::cerr << std::endl;
    std::cerr << "Writing to '" << out << "'" << std::endl;

    std::unique_ptr<supersonic::FileSeries> file_series =
        supersonic::EnumeratedFileSeries(out);
    supersonic::FailureOrOwned<supersonic::WritableRawStorage>
        writable_storage_result =
            supersonic::WritableFileStorage<BenchmarkingFile>(
                std::move(file_series),
                allocator);
    CHECK_FAILURE(writable_storage_result);
    std::unique_ptr<supersonic::WritableRawStorage>
        writable_storage(writable_storage_result.release());

    supersonic::FailureOrOwned<supersonic::SchemaPartitioner> partitioner_result =
        supersonic::CreateFixedSizeSchemaParitioner(family_size);
    CHECK_FAILURE(partitioner_result);
    std::unique_ptr<supersonic::SchemaPartitioner> partitioner(partitioner_result.release());

    supersonic::FailureOrOwned<supersonic::Sink> storage_sink_result =
        supersonic::CreateMultiFilesStorageSink(tuple_schema,
                                                std::move(writable_storage),
                                                  std::move(partitioner),
                                                allocator);
    CHECK_FAILURE(storage_sink_result);
    std::unique_ptr<supersonic::Sink> storage_sink(storage_sink_result.release());

    supersonic::View view(table.view());

    BenchmarkingFile::timer = new boost::timer::cpu_timer();
    BenchmarkingFile::timer->stop();
    boost::timer::cpu_timer timer;
    while (view.row_count() > 0) {
      supersonic::View chunk(view);
      if (chunk.row_count() > batch_size) {
        chunk.set_row_count(batch_size);
      }
      CHECK_FAILURE(storage_sink->Write(chunk));
      view.Advance(batch_size < view.row_count() ? batch_size : view.row_count());
    }
    CHECK_FAILURE(storage_sink->Finalize());

    BenchmarkingFile::timer->resume();
    sync();
    BenchmarkingFile::timer->stop();
    timer.stop();

    double elapsed_app = timer.elapsed().wall - BenchmarkingFile::timer->elapsed().wall;
    double elapsed = timer.elapsed().wall;
    double ratio = elapsed_app / elapsed;

    if (ratio < 0.5) {
      std::cerr << "Ratio looks strange, repeating test!" << std::endl;
      repeat = true;
      continue;
    }

    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::fixed << std::showpoint;
    std::cout.precision(5);
    std::cout << out << ", " << elapsed << ", " << elapsed_app << ", " <<
        ratio << ", " << data_size << std::endl;

    std::cerr << "Elapsed time: " << (elapsed / 1000000000.0) << "s" << std::endl;
    std::cerr << "Elapsed app time: " << (elapsed_app / 1000000000.0) << "s" << std::endl;
    std::cerr << "App/wait ratio: " << (elapsed_app / elapsed) << std::endl;
    std::cerr << "Written data: " << (data_size / BYTES_IN_MEG) << "MB" << std::endl;
    std::cerr << "Troughput: " << ((double) data_size / elapsed) * (1000000000.0 / 1024 / 1024) << "MB/s" << std::endl;

     delete BenchmarkingFile::timer;
  } while(repeat);

  }
  }
  }
}
