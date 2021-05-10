from argparse import ArgumentParser, Namespace
from assembler import Assembler
from exceptions import AssemblerException

from filehandler import FileHandler
from preprocessor import PreProcessor


class ArgParser:

    def __init__(self):
        self.args = None

    def parse(self) -> None:
        parser = ArgumentParser('ZioZir assembler')
        parser.add_argument('inputfile', nargs='*')
        parser.add_argument('-o', '--outputfile')
        parser.add_argument('--outhex')
        parser.add_argument('--dumpinstr')

        self.args = parser.parse_args()

    def args_ok(self) -> bool:
        return (self.args.inputfile is not None 
               and self.args.outputfile is not None)


def assemble_pipeline(args: Namespace) -> None:
    # Read input file.
    input = FileHandler.read(args.inputfile)

    # Preprocess.
    input = PreProcessor.process(input)

    # Clear comments.
    input = Assembler.clear_comments(input)
    
    # Create tokens.
    input = Assembler.tokenize(input)

    # Translate labels.
    input = Assembler.labelize(input)

    # Build instructions.
    input = Assembler.build_instructions(input)

    # Parse the instructions.
    input = Assembler.parse_instructions(input)

    print('\n'.join(str(a) for a in input))



if __name__ == '__main__':
    parser = ArgParser()
    parser.parse()

    parser.args.inputfile = '/home/victor/coding/projects/ziozir/assembler/inputtest.zasm'

    assemble_pipeline(parser.args)
