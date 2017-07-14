#include "./mybiginteger.h"
#include "./calculator.h"

#include "tbb/pipeline.h"
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tbb_allocator.h"

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

#include <curses.h>

volatile bool is_finish = false;  // флаг принудительного выхода из приложения
volatile double res_time = 0.;    // Общее время работы программы
/**
 * Запуск pipeline
 */
void run(const char* in_file_path, const char* out_file_path, int num_threads) {
  tbb::task_scheduler_init init(num_threads);
  int ntokens = 20;

  tbb::tick_count start = tbb::tick_count::now();
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
  /**
   * Читает очередную строку из входного файла и передает вычисленное выражение в тред обработки
   */
  tbb::filter_t<void, std::shared_ptr<std::string>> reader(tbb::filter::serial_in_order, [&in_file, &in_file_current_pos, &in_file_size](tbb::flow_control& fc) {
    auto str = std::make_shared<std::string>();
    if (in_file.eof() || is_finish) {
      fc.stop();
      if (in_file.eof()) {
        in_file_current_pos = in_file_size;
      }
    } else {
      in_file_current_pos = in_file.tellg();
      std::getline(in_file, *str);
    }
    return str;
  } );
  /**
   * Возвращает результат вычисления выражения
   */
  tbb::filter_t<std::shared_ptr<std::string>, std::shared_ptr<mycalc::BigInteger>> processor(tbb::filter::parallel, [](const std::shared_ptr<std::string>& in) {
    const std::string& expression = *in.get();
    mycalc::Calculator worker(expression);
    return worker.CalcExpression();
  } );
  /**
   * Выводит результат вычисления выражения в выходной файл
   */
  tbb::filter_t<std::shared_ptr<mycalc::BigInteger>, void> writer(tbb::filter::serial_in_order, [&out_file, &in_file_current_pos, &in_file_size, &prev_progress](const std::shared_ptr<mycalc::BigInteger>& result) {
    if (result) {
      out_file << *result << std::endl;
    } else {
      out_file << "Invalid expression" << std::endl;
    }

    int progress = 100 * in_file_current_pos / in_file_size;
    if (prev_progress != progress) {
      prev_progress = progress;
      std::cout << std::setprecision(2) << std::fixed << progress << " % \r";
      std::fflush(stdout);
    }
  } );

  tbb::filter_t<void,void> pipeline = reader & processor & writer;

  tbb::parallel_pipeline(ntokens, pipeline);
  tbb::tick_count finish = tbb::tick_count::now();
  res_time = (finish - start).seconds();
  // std::cout << "Time = " << (finish - start).seconds() << " s" << std::endl;
  is_finish = true;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "Usage: <app> <in_file> <out_file> [<num_threads>]" << std::endl;
    return 1;
  }

  char* in_file_path = argv[1];
  char* out_file_path = argv[2];
  int num_threads = argc > 3 ? std::stoi(argv[3]) : tbb::task_scheduler_init::automatic;

  initscr();
  timeout(200);

  std::thread processor(run, in_file_path, out_file_path, num_threads);

  while (!is_finish) {
    char c = getch();
    if (c == 'q') {
      is_finish = true;
    }
  }

  processor.join();
  endwin();

  std::cout << "Work has finished!" << std::endl;
  std::cout << "Time = " << res_time << " s" << std::endl;
  return 0;
}
