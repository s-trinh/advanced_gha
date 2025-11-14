#!/usr/bin/env python3
#
# Copyright (C) 2025 s-trinh
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# this program.  If not, see <http://www.gnu.org/licenses/>.
#
import argparse
import numpy as np
import sys

def main():
    parser = argparse.ArgumentParser(description='Read NPZ file using NumPy.')
    parser.add_argument("-i", "--input", type=str, required=True, help="Input data")
    args = parser.parse_args()

    input_npz = args.input
    print(f"Load: {input_npz}")

    data_dict = np.load(input_npz)
    for key, value in data_dict.items():
        print(f"key: {key} ; value: {value} ; shape: {value.shape}")

if __name__ == '__main__':
    main()