class BaseException(Exception):

    def __init__(self, msg: str, row: int):
        super().__init__(msg)
        self.row = row
    
        
class AssemblerException(BaseException):

    def __init__(self, msg: str, row: int):
        super().__init__(msg, row)
    

class PreProcessException(BaseException):

    def __init__(self, msg: str, row: int):
        super().__init__(msg, row)
