class FileHandler:

    @classmethod
    def read(cls, filepath: str) -> str:
        """ Reads file from disk and returns the content as a string. """
        with open(filepath) as f:
            return f.read()

    @classmethod
    def save(cls, data: bytes, filepath: str, mode: str ='wb') -> None:
        """ Saves data to the given filepathy. """
        with open(filepath, mode) as f:
            f.write(data)
