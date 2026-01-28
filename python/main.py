""" main.py 
Parses arguments and runs main program
"""
import sys
import argparse

from typing import List

from IPAencdec import IPAEncoderDecoder


def make_parser():
    parser = argparse.ArgumentParser()

    parser.add_argument("dirpath", help="Directory path for the project")
    parser.add_argument(
        "chartnames", nargs=2, help="Names of the charts to get encodings from"
    )
    parser.add_argument("filenames", nargs="*", default=None, help="Files to decode")

    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("-e", "--encode", action="store_true", help="Encode file")
    group.add_argument("-d", "--decode", action="store_true", help="Decode file")

    return parser


def main(args: List[str]):
    parser = make_parser()
    arguments = parser.parse_args(args)
    if arguments.encode:
        arguments.filenames = arguments.chartnames
    else:
        try:
            assert arguments.filenames
        except:
            print("Error: No filepath for decoding")
            raise ValueError
    encdec = IPAEncoderDecoder(
        arguments.dirpath, arguments.chartnames, arguments.filenames
    )
    encdec.compute_encodings()
    if arguments.encode:
        encdec.encode_files()
    else:
        encdec.decode_files()


if __name__ == "__main__":
    main(sys.argv[1:])
