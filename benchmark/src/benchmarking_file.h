#ifndef _BENCHMARKING_FILE_H_
#define _BENCHMARKING_FILE_H_

#include <boost/timer/timer.hpp>
#include <supersonic/utils/file.h>

class BenchmarkingFile : public File {
 public:
  static string JoinPath(const string& dirname, const string& basename) {
    return File::JoinPath(dirname, basename);
  }

  bool Exists() const {
    return file_->Exists();
  }

  bool Open() {
    return file_->Open();
  }

  bool Delete() {
    return file_->Delete();
  }

  bool Close() {
    return file_->Close();
  }

  int64 Read(void* buffer, uint64 length) {
    timer->resume();
    int64 result = file_->Read(buffer, length);
    timer->stop();
    return result;
  }

  char* ReadLine(char* buffer, uint64 max_length) {
    timer->resume();
    char* result = file_->ReadLine(buffer, max_length);
    timer->stop();
    return result;
  }

  int64 Write(const void* buffer, uint64 length) {
    timer->resume();
    int64 result = file_->Write(buffer, length);
    timer->stop();
    return result;
  }

  int64 Size() {
    return file_->Size();
  }

  bool eof() {
    return file_->eof();
  }

  bool Seek(int64 position) {
    timer->resume();
    bool result = file_->Seek(position);
    timer->stop();
    return result;
  }

  static File* Create(const std::string& file_name,
                      const std::string& mode) {
    File* f = File::Create(file_name, mode);
    if (f != nullptr) {
      return new BenchmarkingFile(file_name, f);
    } else {
      return f;
    }
  }

  static bool Exists(const string& fname) {
    return File::Exists(fname);
  }

  static boost::timer::cpu_timer* timer;

 private:
  BenchmarkingFile(const std::string& file_name,
                   File* file)
      : File(file_name),
        file_(file) {}
  virtual ~BenchmarkingFile() {}

  File* file_;
};

boost::timer::cpu_timer* BenchmarkingFile::timer = nullptr;

#endif  // _BENCHMARKING_FILE_H_
