/*
 * Copyright (C) 2025 s-trinh
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <visp3/core/vpConfig.h>
#include <visp3/core/vpIoTools.h>

int main(int argc, char *argv[])
{
  std::string filename = "";
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-i" && i + 1 < argc) {
      filename = std::string(argv[++i]);
    } else {
      std::cout << "Usage: print_npz_simple -i <path_to_file.npz>" <<std::endl;
      return EXIT_SUCCESS;
    }
  }

  try {
    if (!filename.empty()) {
      std::cout << "Read: filename=" << filename << std::endl;
      visp::cnpy::npz_t npz_data = visp::cnpy::npz_load(filename);
      for (auto data : npz_data) {
        std::cout << "data: " << data.first << " ; num_vals=" << data.second.num_vals << " ; shape: ";
        for (auto sh : data.second.shape) {
          std::cout << sh << "x";
        }
        std::cout << std::endl;

        if (data.second.num_vals == 1) {
          if (data.second.data_type == 'b') {
            std::cout << "Value: " << *data.second.data<bool>() << std::endl;
          } else if (data.second.data_type == 'u' && data.second.word_size == 4) {
            std::cout << "Value: " << *data.second.data<uint32_t>() << std::endl;
          } else if (data.second.data_type == 'i' && data.second.word_size == 8) {
            std::cout << "Value: " << *data.second.data<int64_t>() << std::endl;
          } else if (data.second.data_type == 'f' && data.second.word_size == 4) {
            std::cout << "Value: " << *data.second.data<float>() << std::endl;
          } else if (data.second.data_type == 'f' && data.second.word_size == 8) {
            std::cout << "Value: " << *data.second.data<double>() << std::endl;
          } else if (data.second.data_type == 'U') {
            std::vector<std::string> vec_string = data.second.as_utf8_string_vec();
            for (auto str : vec_string) {
              std::cout << "Value: " << str << std::endl;
            }
          }
        } else {
          // TODO:
          if (data.second.data_type == 'U') {
            std::vector<std::string> vec_string = data.second.as_utf8_string_vec();
            for (auto str : vec_string) {
              std::cout << "Value: " << str << std::endl;
            }
          }
        }
      }
    } else {
      std::cerr << "Empty filepath!" << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << "Catch exception in print_npz_simple: " << e.what() << std::endl;
  return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
