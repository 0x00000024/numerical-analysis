#include "my_solver.h"

std::tuple<int, int> findIndex(double sample_start, double sample_end, const std::vector<double> &sample) {
  int index_start = 0;
  int index_end = 0;

  for (int i = 0; i < sample.size() - 1; ++i) {
    if (sample[i] >= sample_start) {
      index_start = i;
      break;
    }
  }

  for (int i = sample.size() - 1; i >= 0; --i) {
    if (sample[i] <= sample_end) {
      index_end = i;
      break;
    }
  }

  return std::make_tuple(index_start, index_end);
}

double intervalPdf
    (const int &index_start, const int &index_end, const double &delta_h, const std::vector<double> &probability) {
  double square_area = 0;
  double total_square_area = 0;
  double probability_density = 0;

  for (int i = index_start; i < index_end; ++i) {
    square_area = (probability[i] + probability[i + 1]) / 2.0 * delta_h;
    total_square_area += square_area;
  }

  probability_density = total_square_area;
  return probability_density;
}

double samplePdf(const double &p, const double &probability_density) {
  return p / probability_density;
}

void generatePdf() {
  std::ifstream ifs;
  std::ofstream ofs;

  int sample_num = 0;
  double delta_h = 0;
  double sample_temp = 0, probability_temp = 0;

  std::vector<double> sample;
  std::vector<double> probability;

  double sample_start = 0;
  double sample_end = 0;
  double sample_interval = 0;

  double square_area = 0;
  double total_square_area = 0;
  double probability_density = 0;
  double pdf_result = 0;
  int index_start = 0;
  int index_end = 0;

  // Open text file for reading and writing data
  ifs.open("../sampling_table.txt");
  if (!ifs.is_open()) {
    std::cerr << "[Error] cannot open sampling_table.txt" << std::endl;
    return;
  }
  ofs.open("../pdf_table.txt");
  if (!ofs.is_open()) {
    std::cerr << "[Error] cannot open pdf_table.txt" << std::endl;
    return;
  }

  // Read data from text file
  ifs >> sample_num;
  ifs >> delta_h;
  while (ifs >> sample_temp) {
    sample.push_back(sample_temp);
    ifs >> probability_temp;
    probability.push_back(probability_temp);
  }

  sample_start = sample.front();
  sample_end = sample.back();
  sample_interval = sample_end - sample_start;

  // Normalization for sample
  for (auto &s : sample) {
    s = (s - sample_start) / sample_interval;
  }

  // Calculate pdf for each sample
  for (int i = 0; i < probability.size() - 1; ++i) {
    square_area = (probability[i] + probability[i + 1]) / 2.0 * delta_h;
    total_square_area += square_area;
  }

  probability_density = total_square_area / sample_interval;

  for (auto &p : probability) {
    pdf_result = samplePdf(p, probability_density);
    p = pdf_result;
  }

  // Write sample pdf data to text file
  delta_h = sample[1] - sample[0];
  ofs << sample_num << " ";
  ofs << std::fixed << delta_h << std::endl;
  for (int i = 0; i < sample_num; ++i) {
    ofs << std::setw(7) << std::left << sample[i] << " ";
    ofs << std::setw(7) << std::left << probability[i] << std::endl;
  }

  std::cout.precision(6);
  std::tie(index_start, index_end) = findIndex(0.0, 1.0, sample);
  pdf_result = intervalPdf(index_start, index_end, delta_h, probability);
  std::cout << "*** Integrating the pdf from 0.0 to 1.0 = " << pdf_result << std::endl;

  std::tie(index_start, index_end) = findIndex(0.0, 0.25, sample);
  pdf_result = intervalPdf(index_start, index_end, delta_h, probability);
  std::cout << "*** Integrating the pdf from 0.0 to 0.25 = " << std::fixed << pdf_result << std::endl;

  std::tie(index_start, index_end) = findIndex(0.25, 0.5, sample);
  pdf_result = intervalPdf(index_start, index_end, delta_h, probability);
  std::cout << "*** Integrating the pdf from 0.25 to 0.5 = " << std::fixed << pdf_result << std::endl;

  std::tie(index_start, index_end) = findIndex(0.5,0.75, sample);
  pdf_result = intervalPdf(index_start, index_end, delta_h, probability);
  std::cout << "*** Integrating the pdf from 0.5 to 0.75 = " << std::fixed << pdf_result << std::endl;

  std::tie(index_start, index_end) = findIndex(0.75,1.0, sample);
  pdf_result = intervalPdf(index_start, index_end, delta_h, probability);
  std::cout << "*** Integrating the pdf from 0.75 to 1.0 = " << pdf_result << std::endl;

  ifs.close();
  ofs.close();
}
