import socket
import struct
import threading

WORD_FORMAT = 'H'


class MemoryType:
    RAM = 0
    REGS = 1
    FLASH = 2


class Action:
    ACTION_READ = 1
    ACTION_WRITE = 2
    ACTION_MEM_INFO = 3
    ACTION_EXECUTE = 4
    ACTION_RESET = 5


class CpuClient(threading.Thread):

    PORT = 8999

    def __init__(self):
        super().__init__(daemon=True)
        self._sock: socket = None

    def execute_one_instruction(self) -> None:
        """ Executes a single instruction. """
        # | action |
        # |   0   |
        self._send(struct.pack('<B', Action.ACTION_EXECUTE))

    def reset(self) -> None:
        """ Resets the emulator. """
        self._send(struct.pack('<B', Action.ACTION_RESET))

    def read_memory_info(self) -> dict:
        """ Reads memory information and returns a dictionary
            with the size of each memory type.
        """
        # | action |
        # |   0   |
        self._send(struct.pack('<B', Action.ACTION_MEM_INFO))

        # | regs | bios | ram  | flash |
        # | 0-3  | 4-7  | 8-11 | 12-15 |
        regs, bios, ram, flash = self._sock.recv(struct.calcsize('<IIII'))
        return {
            'regs': regs,
            'bios': bios,
            'ram': ram,
            'flash': flash
        }

    def read(self, mem_type: int, addr_from: int, addr_to: int) -> list:
        """ Reads from memory of type mem_type from address addr_from
            to addr_to.
        """
        #  action | mem_type | addr_from | addr_to |
        #     0   |     1    |   2-5     |   6-9   |
        payload = struct.pack('<BBII', Action.ACTION_READ, mem_type, addr_from,
                              addr_to)
        self._send(payload)

        # | len |  data |
        # |  0  | 1..*  |
        length = struct.unpack('<I', self._sock.recv(4))
        data = self._sock.recv(length)

        return data

    def write(self, mem_type: int, addr: int, value: int) -> None:
        """ Writes value into address addr of memory type mem_type. """
        #  action | mem_type | addr | value |
        #     0   |     1    |  2-5 |  6-9  |
        payload = struct.pack('<BBII', Action.ACTION_WRITE, mem_type, addr,
                              value)
        self._send(payload)

    def _send(self, payload: bytes) -> None:
        if self._sock is None:
            self.connect()
        self._sock.send(payload)

    def connect(self) -> None:
        if self._sock is None:
            self._sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._sock.connect(('localhost', CpuClient.PORT))

    def disconnect(self) -> None:
        if self._sock is not None:
            self._sock.close()
            self._sock = None

    def run(self) -> None:
        pass
