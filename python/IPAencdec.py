""" IPAencdec.py
This file encodes the IPA charts into integers and decodes back to IPA
"""
from __future__ import annotations

import os

from typing import List


class IPAEncoderDecoder:
    """
    IPAEncoderDecoder encodes and decodes files from IPA/integers to integers/IPA
    """

    def __init__(
        self: IPAEncoderDecoder,
        dirpath: str,
        chartpaths: List[str],
        filenames: List[str],
    ):
        self.chartpaths = chartpaths
        self.filenames = filenames
        self.dirpath = dirpath
        self._maxkey = 0
        self._ctoi = dict()
        self._itoc = dict()

    def _encodechars(self: IPAEncoderDecoder, filecontents: str):
        for line in filecontents:
            for chartuple in line.split("|"):
                for ch in chartuple.split(","):
                    try:
                        assert ch not in self._ctoi
                        self._ctoi[ch] = self._maxkey
                        self._itoc[self._maxkey] = ch
                        self._maxkey += 1
                    except AssertionError:
                        print(
                            f"Warning: {ch} already in encodings (encoded to {self._ctoi[ch]})"
                        )

    def compute_encodings(self: IPAEncoderDecoder):
        for chartname in self.chartpaths:
            with open(os.path.join(self.dirpath, chartname), "r") as f:
                self._encodechars(f.read())

    def encode_files(self: IPAEncoderDecoder):
        for filename in self.filenames:
            self._encode_file(self.dirpath, filename)

    def _encode_file(self: IPAEncoderDecoder, dirpath: str, filepath: str):
        encoded_filepath = "encoded." + filepath
        encoded_data = []
        with open(os.path.join(dirpath, filepath), "r") as f:
            filecontents = f.read()
            for line in filecontents:
                encline = []
                for chartuple in line.split("|"):
                    enctuple = []
                    for ch in chartuple.split(","):
                        enctuple.append(self._ctoi[ch])
                    encline.append(",".join(enctuple))
                encoded_data.append("|".join(encline))
        data = "\n".join(encoded_data)
        with open(os.path.join(dirpath, encoded_filepath), "w") as f:
            f.write(data)

    def decode_files(self: IPAEncoderDecoder):
        for filename in self.filenames:
            self._decode_file(self.dirpath, filename)

    def _decode_file(self: IPAEncoderDecoder, dirpath: str, filepath: str):
        decoded_filepath = "decoded." + filepath
        decoded_data = []
        with open(os.path.join(dirpath, filepath), "r") as f:
            filecontents = f.read()
            for line in filecontents:
                encodedchars = line.split(".")
                decodedchars = ""
                for encchar in encodedchars:
                    decodedchars += self._itoc[encchar]
                decoded_data.append(decodedchars)
        data = "\n".join(decoded_data)
        with open(os.path.join(dirpath, decoded_filepath), "w") as f:
            f.write(data)
