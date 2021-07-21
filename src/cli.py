# coding=utf-8
""" Main compile function that calls the CLI """
from parac.compiler import __main__
from parac.logging import init_rich_console

if __name__ == '__main__':
    init_rich_console()
    __main__.cli()