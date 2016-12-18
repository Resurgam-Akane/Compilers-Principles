# coding=utf8
# ========================================================
#   Copyright (C) 2016 All rights reserved.
#
#   filename : ParserMachine.py
#   author   : xuzhu / xuzhu1996@hotmail.com
#   date     : 2016-10-31
#   desc     : create a analysis table
# ========================================================

import Controller
import ParserTable
import sys

# python ParserMachine.py target_string
if __name__ == '__main__':
    if len(sys.argv) == 2:
        words = sys.argv[1]
        controller = Controller.Controller(words.strip())
        Parser_Table = ParserTable.Table()
        Parser_Table.create_table()
        Parser_Table.show()
        print '\n\n'
        controller.run(Parser_Table.table)
    else:
        print 'The number of parameter is 1, your input is not correct.'

