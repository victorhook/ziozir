"""
    Assembly instruction format:
    Label (opt)  | Instruction mnemonic | Operand(s) (opt) | Comment (opt)
"""

import logging


from assembler.preprocessor import pre_process



class Instruction:
    pass


class Token:
    pass


class Assembler:

    @classmethod
    def read_file(cls, filepath: str) -> str:
        """ Reads file from disk and returns the content as a string. """
        with open(filepath) as f:
            return f.read()

    @classmethod
    def save_file(cls, data: bytes, filepath: str) -> None:
        """ Saves data to the given filepath as binary. """
        with open(filepath, 'wb') as f:
            f.write(data)

    @classmethod
    def convert_to_binary(cls, input: list) -> bytes:
        """ Converts a list of instructions into bytes. """
        return input

    @classmethod
    def parse(cls, tokens: list) -> list:
        """ Parses a list of tokens and returns a list of instructions. """
        return tokens

    @classmethod
    def tokenize(cls, input: str) -> list:
        """ Tokenizes the input string into a list of tokens. """
        return input

    @classmethod
    def get_outputpath(cls, outputpath: str) -> str:
        """ Returns a correct filepath that the output file can be saved
            to.
        """
        return outputpath

    @staticmethod
    def assemble(sourcepath: str, output: str = None) -> None:
        logging.debug(f'Reading input {sourcepath}')
        data = Assembler.read_file(sourcepath)

        logging.debug(f'Tokenizing data')
        tokens = Assembler.tokenize(data)

        logging.debug(f'Parsing tokens into instructions')
        instructions = Assembler.parse(tokens)

        logging.debug(f'Turning instructions into binary data')
        binary = Assembler.convert_to_binary(instructions)

        output = Assembler.get_outputpath(output)
        logging.debug(f'Saving binary data to output path {output}')
        Assembler.save_file(binary, output)


if __name__ == '__main__':
    pass