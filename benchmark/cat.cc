#include <time.h>

#include <boost/algorithm/string.hpp>
#include <boost/timer/timer.hpp>
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
#include <supersonic/contrib/storage/base/page.h>
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
  if (argc < 4) {
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
  if (query == -1) {
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

/*
int all_pages = 0;

while (readable_storage->HasNext()) {
  supersonic::FailureOrOwned<supersonic::RandomPageReader> page_reader_result =
      readable_storage->NextRandomPageReader();
  CHECK_FAILURE(page_reader_result);
  std::unique_ptr<supersonic::RandomPageReader>
      page_reader(page_reader_result.release());
  supersonic::RandomPageReader* x = page_reader.get();

  supersonic::FailureOrOwned<supersonic::DataStorage> storage_result =
      supersonic::CreateDataStorage(std::move(page_reader), allocator);
  CHECK_FAILURE(storage_result);
  std::unique_ptr<supersonic::DataStorage> storage(storage_result.release());

//  std::cout << "-- New file --" << std::endl;
  supersonic::StorageMetadata meta = storage->Metadata();
  for (supersonic::PageFamily family : meta.page_families()) {
//    std::cout << "Reading family: " << family.family_number() << std::endl;
    long max = 0;
//    std::cout << "Num pages: " << family.pages_size() << std::endl;
    all_pages += family.pages_size();
    for (supersonic::PageMetadata page_meta : family.pages()) {
      supersonic::FailureOr<const supersonic::Page*> page_result =
          x->GetPage(family.family_number(), page_meta.page_number());
      CHECK_FAILURE(page_result);
      max = fmax(max, page_result.get()->PageHeader().total_size);
//      std::cout << "Page size: " << page_result.get()->PageHeader().total_size << std::endl;;
    }
//    std::cout << "max: " << max << std::endl;
  }
}
std::cout << "All pages:" << all_pages << std::endl;
*/


  supersonic::FailureOrOwned<supersonic::Cursor> storage_scan_result =
      supersonic::MultiFilesScan(std::move(readable_storage),
                     offset,
                     schema,
                     allocator);
  CHECK_FAILURE(storage_scan_result);
  std::unique_ptr<supersonic::Cursor>
      storage_scan(storage_scan_result.release());

  supersonic::ViewPrinter printer(false, true);
  long read_lines = 0;
  long pulls = 0;
  supersonic::ResultView result_view = supersonic::ResultView::EOS(); 
  boost::timer::cpu_timer timer;
  do {
    pulls++;
    result_view = storage_scan->Next(batch_size);
    CHECK_FAILURE(result_view);
    if (result_view.has_data()) {
      read_lines += result_view.view().row_count();
      //printer.AppendViewToStream(result_view.view(), &std::cout);
    }
  } while(!result_view.is_eos());
  timer.stop();

  std::cout << filename << ", " << batch_size << ", " << offset << ", " << timer.elapsed().wall << std::endl;

  std::cerr << "Read " << read_lines << " rows from storage." << std::endl;

}
