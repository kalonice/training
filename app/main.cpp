#include "tbb/pipeline.h"
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_allocator.h"
#include "./mybiginteger.h"
#include "./calculator.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <memory>

void run(const char* in_file_path, const char* out_file_path, int ntokens) {
  std::ifstream in_file(in_file_path);
  std::ofstream out_file(out_file_path);

  if (!in_file.is_open() || !out_file.is_open()) {
    std::cerr << "Invalid files path" << std::endl;
    return;
  }

  in_file.seekg (0, in_file.end);
  int in_file_size = in_file.tellg();
  in_file.seekg (0, in_file.beg);

  int in_file_current_pos = 0;
  int prev_progress = -1;

  tbb::filter_t<void, std::shared_ptr<std::string>> reader(tbb::filter::serial_in_order, [&in_file, &in_file_current_pos, &in_file_size](tbb::flow_control& fc) {
    auto str = std::make_shared<std::string>();
    if (in_file.eof()) {
      fc.stop();
      in_file_current_pos = in_file_size;
    } else {
      std::getline(in_file, *str);
      in_file_current_pos = in_file.tellg();
    }
    return str;
  } );

  tbb::filter_t<std::shared_ptr<std::string>, std::string> processor(tbb::filter::parallel, [](std::shared_ptr<std::string>& in) {
    const std::string& expression = *in.get();
    mycalc::Calculator worker(expression);
    auto result = worker.CalcExpression();
    if (result) {
      return result->GetValue();
    } else {
      return std::string("Invalid expression");
    }
  } );

  tbb::filter_t<std::string, void> writer(tbb::filter::serial_in_order, [&out_file, &in_file_current_pos, &in_file_size, &prev_progress](const std::string& in) {
   out_file << in << std::endl;

    int progress = 100 * in_file_current_pos / in_file_size;
    if (prev_progress != progress) {
      prev_progress = progress;
      std::cout << std::setprecision(2) << std::fixed << progress << " % \r";
      std::fflush(stdout);
    }
  } );

  tbb::filter_t<void,void> pipeline = reader & processor & writer;

  tbb::parallel_pipeline(ntokens, pipeline);
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Usage: <app> <in-file> <out-file> <num_threads>" << std::endl;
    return 1;
  }

  char* in_file_path = argv[1];
  char* out_file_path = argv[2];
  int num_threads = atoi(argv[3]);
  int ntokens = 20;

  tbb::task_scheduler_init init(num_threads);
  tbb::tick_count start = tbb::tick_count::now();
  //run(in_file_path, out_file_path, 16);
  std::thread processor(run, in_file_path, out_file_path, 16);
  processor.join();
  tbb::tick_count finish = tbb::tick_count::now();


  std::cout << "Time = " << (finish - start).seconds() << " s" << std::endl;

  return 0;
}
