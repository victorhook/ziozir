"""
    Assembly instruction format:
    Label (opt)  | Instruction mnemonic | Operand(s) (opt) | Comment (opt)
"""
import logging
import re

from exceptions import AssemblerException
from line import Line
from instructions import InstructionFactory, Instruction



class Assembler:

    _re_comments = re.compile(';.*')
    _re_label = re.compile('[a-zA-Z_][a-zA-Z_0-9]+:')
    
    @classmethod
    def _get_row_tokens(cls, row: str) -> list:
        """ Returns the tokens from the given string row.
            Returns None if there are no tokens in this row.
        """
        tokens = list(filter(len, row.split(' ')))
        if not tokens:
            tokens = None
        return tokens

    @classmethod
    def _trim_label_name(cls, name: str) -> str:
        return name[:-1]

    @classmethod
    def _is_label(cls, name: str) -> str:
        if name is None:
            return False

        if type(name) is list:
            name = name[0]
        
        return type(cls._re_label.match(name)) is re.Match

    @classmethod
    def _get_labels(cls, lines: list) -> dict:
        """ Returns a dictionary of labels with format: Name : Address. """
        # Name : Address
        labels = {}

        # Get all lines that has tokens.
        for line in lines:
            
            # Check if the first token is a label.
            label_name = line.tokens[0]
            
            if cls._is_label(label_name):
                label_name = cls._trim_label_name(label_name)

                # Ensure each label is only defined once!
                if label_name in labels:
                    raise AssemblerException(f'Label {label_name} already '
                                             'defined', line.real_line)
                
                # The address of the label is its address + 1.
                labels[label_name] = line.code_line + 1

        return labels

    @classmethod
    def _replace_labels_with_addresses(cls, lines: list, labels: dict) -> list:
        """ Replaces all label references with the label address. """
        # Replace all label names with the label address.
        for line in lines:

            if line.tokens is not None:

                for index, token in enumerate(line.tokens):
                    if token in labels:
                        address = labels[token]
                        line.tokens[index] = address
        
        return lines

    
    @classmethod
    def _get_lines_with_content(cls, lines: list, 
                                with_labels : bool = True) -> list:
        if with_labels:
            return filter(lambda line: line.tokens, lines)
        else:
            return filter(lambda line: line.tokens and 
                                       not cls._is_label(line.tokens), lines)

    # 1.
    @classmethod
    def clear_comments(cls, input: str) -> list:
        """ Clears all comments from the input string. """
        return cls._re_comments.sub('', input)

    # 2.
    @classmethod
    def tokenize(cls, input: str) -> list:
        """ Tokenizes the input string into a list of tokens. """
        
        code_lines = []
        valid_code_line = 0
        for row_nbr, row in enumerate(input.splitlines()):
            # Check if current line has any content.
            tokens = cls._get_row_tokens(row)
            
            # We want to keep track of the current (valid) code line as well
            # as the raw input rows.
            if tokens is not None and not cls._is_label(tokens):
                valid_code_line += 1

            # Create a new code-line.
            line = Line(row_nbr, valid_code_line, tokens)
            code_lines.append(line)

        return code_lines

    # 3.
    @classmethod
    def labelize(cls, lines: list) -> list:
        """ Replaces all labels with the address value. """

        # We only care about the lines with any tokens right now.
        lines_with_tokens = cls._get_lines_with_content(lines)

        # Get all the labels from the lines.
        labels = cls._get_labels(lines_with_tokens)

        # Replace all label references with the labels address.
        lines = cls._replace_labels_with_addresses(lines, labels)

        return lines

    # 4.
    @classmethod
    def build_instructions(cls, lines: list) -> list:
        """ Builds a list of lines and returns a list of instructions. """
        instructions = []

        for line in cls._get_lines_with_content(lines, with_labels=False):
            instr = InstructionFactory.build_instruction(line)

            if not instr.is_valid:
                raise AssemblerException(f'Not a valid instruction: {instr}')

            instructions.append(instr)

        return instructions

    # 5.
    @classmethod
    def parse_instructions(cls, instructions: list) -> list:
        """ Parses a list of lines and returns a list of instructions. """
        return instructions

    # 6.
    @classmethod
    def convert_to_binary(cls, input: list) -> bytes:
        """ Converts a list of instructions into bytes. """
        return input

