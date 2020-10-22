#include "my_solver.h"

void generateHistogram() {
  auto start = std::chrono::high_resolution_clock::now();

  std::ifstream ifs;
  std::ofstream ofs;

  double sample_num = 0;
  double delta_h = 0;
  double sample_temp = 0;
  double probability_temp = 0;
  double temp = 0;

  std::vector<double> sample;
  std::vector<double> pseudorandom_number;

  // Read sample data from pdf text file
  ifs.open("../pdf_table.txt");
  if (!ifs.is_open()) {
    std::cerr << "[Error] cannot open pdf_table.txt" << std::endl;
    return;
  }

  ifs >> sample_num;
  ifs >> delta_h;

  while (ifs >> sample_temp) {
    sample.push_back(sample_temp);
    ifs >> probability_temp;
  }

  ifs.close();
  ifs.clear();

  // Read pseudorandom number from random event table file
  ifs.open("../random_event_table.txt");
  if (!ifs.is_open()) {
    std::cerr << "[Error] cannot open random_event_table.txt" << std::endl;
    return;
  }

  ifs >> temp;

  while (ifs >> temp) {
    pseudorandom_number.push_back(temp);
  }

  // Write result to histogram file
  ofs.open("histogram.txt");
  if (!ofs.is_open()) {
    std::cerr << "[Error] cannot open histogram.txt" << std::endl;
    return;
  }

  int match = 0;
  for (int i = 0; i < sample.size() - 1; ++i) {
    match = 0;
    for (auto p : pseudorandom_number) {
      if (p > sample[i] && p <= sample[i + 1]) ++match;
    }
    ofs << std::fixed << std::setprecision(6) << sample[i] << " ~ " << sample[i + 1] << ": " << match << std::endl;
  }

  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "The generateHistogram run time is " << duration.count() << "(ms).." << std::endl;

  ifs.close();
  ofs.close();
}
