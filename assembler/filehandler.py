import binascii
import io


class FileHandler:

    MAX_HEX_BYTES_PER_ROW = 10

    @classmethod
    def read(cls, filepath: str) -> str:
        """ Reads file from disk and returns the content as a string. """
        with open(filepath) as f:
            return f.read()

    @classmethod
    def _save_as_str(cls, data: bytes, filepath: str,
                     formatter: callable) -> None:
        # Group by every byte, seperate by whitespace
        buf = io.StringIO()
        i = 0
        byte_nbr = 0
        for byte in data:
            if byte_nbr > cls.MAX_HEX_BYTES_PER_ROW:
                buf.write('\n')
                byte_nbr = 0

            buf.write(formatter(byte) + ' ')
            i += 2
            byte_nbr += 1

        buf.seek(0)
        cls._save(buf.read(), filepath, mode='w')

    @classmethod
    def save_hex(cls, data: bytes, filepath: str) -> None:
        cls._save_as_str(data, filepath, lambda byte:
                         hex(byte)[2:].zfill(2).upper())

    @classmethod
    def save_bin(cls, data: bytes, filepath: str) -> None:
        cls._save_as_str(data, filepath, lambda byte:
                         bin(byte)[2:].zfill(8))

    @classmethod
    def save_exe(cls, data: bytes, filepath: str) -> None:
        cls._save(data, filepath)

    @classmethod
    def _save(cls, data: bytes, filepath: str, mode: str = 'wb') -> None:
        """ Saves data to the given filepathy. """
        with open(filepath, mode) as f:
            f.write(data)
