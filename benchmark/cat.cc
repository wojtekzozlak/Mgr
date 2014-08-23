#include <time.h>

#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <supersonic/base/infrastructure/tuple_schema.h>
#include <supersonic/base/memory/memory.h>
#include <supersonic/cursor/base/cursor.h>
#include <supersonic/cursor/infrastructure/table.h>
#include <supersonic/cursor/infrastructure/view_printer.h>
#include <supersonic/contrib/storage/base/raw_storage.h>
#include <supersonic/contrib/storage/core/file_storage.h>
#include <supersonic/contrib/storage/core/file_series.h>
#include <supersonic/contrib/storage/core/storage_scan.h>
#include <supersonic/contrib/storage/core/storage_sink.h>
#include <supersonic/contrib/storage/util/path_util.h>
#include <supersonic/utils/file.h>

#include "src/schema.h"

#define CHECK_FAILURE(x) {\
  if (x.is_failure()) { \
    std::cerr << x.exception().ToString();\
    exit(1);\
  }\
}

int main(int argc, const char* argv[]) {
  if (argc < 5) {
    std::cout << "Usage: " << argv[0] << " FILENAME BATCH_SIZE OFFSET [QUERY]" << std::endl;
    return 1;
  }
  int query = -1;
  const char* filename = argv[1];
  int batch_size = atoi(argv[2]);
  int offset = atoi(argv[3]);
  if (argc > 4) {
    query = atoi(argv[4]);
  }

  supersonic::TupleSchema schema;
  if (query == 0) {
    schema = lineitem_schema();
  } else if (query == 1) {
    schema = Q1();
  } else if (query == 2) {
    schema = Q2();
  } else if (query == 3) {
    schema = Q3();
  } else if (query == 4) {
    schema = Q4();
  } else if (query == 5) {
    schema = Q5();
  } else if (query == 6) {
    schema = Q6();
  } else if (query == 7) {
    schema = Q7();
  } else if (query == 8) {
    schema = Q8();
  } else if (query == 9) {
    schema = Q9();
  } else if (query == 10) {
    schema = Q10();
  } else if (query == 12) {
    schema = Q12();
  } else if (query == 14) {
    schema = Q14();
  } else if (query == 15) {
    schema = Q15();
  } else if (query == 17) {
    schema = Q17();
  } else if (query == 18) {
    schema = Q18();
  } else if (query == 19) {
    schema = Q19();
  } else if (query == 20) {
    schema = Q20();
  } else {
    std::cout << "Unknown query" << std::endl;
    return 1;
  }

  supersonic::BufferAllocator* allocator =
      supersonic::HeapBufferAllocator::Get();

  std::unique_ptr<supersonic::FileSeries> file_series =
      supersonic::EnumeratedFileSeries(filename);
  supersonic::FailureOrOwned<supersonic::ReadableRawStorage>
      readable_storage_result =
          supersonic::ReadableFileStorage<File>(
              std::move(file_series),
              allocator);
  CHECK_FAILURE(readable_storage_result);
  std::unique_ptr<supersonic::ReadableRawStorage>
      readable_storage(readable_storage_result.release());

  supersonic::FailureOrOwned<supersonic::Cursor> storage_scan_result =
      supersonic::MultiFilesScan(std::move(readable_storage),
                     offset,
                     schema,
                     allocator);
  CHECK_FAILURE(storage_scan_result);
  std::unique_ptr<supersonic::Cursor>
      storage_scan(storage_scan_result.release());

  long read_lines = 0;
  supersonic::ViewPrinter printer(false, true);
  supersonic::ResultView result_view = supersonic::ResultView::EOS();
  do {
    result_view = storage_scan->Next(batch_size);
    CHECK_FAILURE(result_view);
    if (result_view.has_data()) {
      read_lines += result_view.view().row_count();
  //    printer.AppendViewToStream(result_view.view(), &std::cout);
    }
  } while(!result_view.is_eos());

  std::cerr << "Read " << read_lines << " rows from storage." << std::endl;
}
