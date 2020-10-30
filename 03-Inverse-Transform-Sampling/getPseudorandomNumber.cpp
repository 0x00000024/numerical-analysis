#include "my_solver.h"

// Use the bisection method to find the index
std::tuple<int, int> findIndex(double uniform_sample, const std::vector<double> &cdf) {
  int index_left = 0;
  int index_right = cdf.size() - 1;
  int index_temp = 0;
  int index_middle = 0;
  int index_break = 0;

  for (int i = 0; i < cdf.size(); ++i) {
    index_middle = (index_left + index_right) / 2;
    // Find the required index and end the loop
    if (index_break == index_middle) break;
    index_break = index_middle;

    index_temp = index_left;
    index_left = index_middle;
    if ((cdf[index_left] - uniform_sample) * (cdf[index_right] - uniform_sample) > 0) {
      index_right = index_middle;
      index_left = index_temp;
    }
  }

  return std::make_tuple(index_left, index_right);
}

std::vector<double>
invertCdf(const std::vector<double> &cdf, const std::vector<double> &sample, const int &pseudorandom_number_size) {
  double uniform_sample = 0;
  std::vector<double> quantile;
  std::srand(std::time(0));
  int index_left = 0, index_right = 0;
  double pseudorandom_number = 0;

  while (quantile.size() < pseudorandom_number_size) {
    uniform_sample = (double) std::rand() / RAND_MAX;
    std::tie(index_left, index_right) = findIndex(uniform_sample, cdf);

    // Using linear interpolation
    pseudorandom_number = sample[index_left] + (uniform_sample - cdf[index_left]) *
        (sample[index_right] - sample[index_left]) / (cdf[index_right] - cdf[index_left]);

    quantile.push_back(pseudorandom_number);
  }

  return quantile;
}

std::vector<double> getCdf(const std::vector<double> &pdf, const double &delta_h) {
  std::vector<double> cdf;
  double cdf_temp = 0;
  for (int i = 0; i < pdf.size(); ++i) {
    cdf_temp = 0;
    for (int j = 0; j < i; ++j) {
      cdf_temp += (pdf[j] + pdf[j + 1]) / 2.0 * delta_h;
    }
    cdf.push_back(cdf_temp);
  }
  return cdf;
}

void getPseudorandomNumber() {
  std::ifstream ifs;
  std::ofstream ofs;

  int sample_num = 0;
  double delta_h = 0;
  double sample_temp = 0;
  double probability_temp = 0;
  std::vector<double> sample;
  std::vector<double> pdf;
  std::vector<double> cdf;
  std::vector<double> quantile;

  int pseudorandom_number_size = 0;

  std::cout << "How many pseudo-random numbers do you need to generate?" << std::endl;
  std::cin >> pseudorandom_number_size;

  ifs.open("../pdf_table.txt");
  if (!ifs.is_open()) {
    std::cerr << "[Error] cannot open pdf_table.txt" << std::endl;
    return;
  }

  ofs.open("../random_event_table.txt");
  if (!ofs.is_open()) {
    std::cerr << "[Error] cannot open random_event_table.txt" << std::endl;
    return;
  }

  ifs >> sample_num;
  ifs >> delta_h;

  while (ifs >> sample_temp) {
    sample.push_back(sample_temp);
    ifs >> probability_temp;
    pdf.push_back(probability_temp);
  }

  cdf = getCdf(pdf, delta_h);

  quantile = invertCdf(cdf, sample, pseudorandom_number_size);

  for (int i = 0; i < quantile.size(); ++i) {
    std::cout << i + 1 << ":  " << std::setprecision(15) << quantile[i] << std::endl;
  }

  std::cout.precision(15);
  ofs << pseudorandom_number_size << std::endl;
  for (int i = 0; i < quantile.size(); ++i) {
    ofs << std::setprecision(15) << quantile[i] << std::endl;
  }

  ifs.close();
  ofs.close();
}
