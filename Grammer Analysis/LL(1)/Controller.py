# coding=utf8
# ========================================================
#   Copyright (C) 2016 All rights reserved.
#
#   filename : Controller.py
#   author   : xuzhu / xuzhu1996@hotmail.com
#   date     : 2016-10-31
#   desc     : create a analysis table
# ========================================================

import sys
import re
import ParserTable

class Controller:
    def __init__(self, words):
        self.stack = ['$', 'E']
        self.input_stack = ['$']
        num_list = re.findall(r"\d+\.?\d*", words)  # use regular expression to match number
        for i in num_list:
            words = words.replace(i, 'n')  # repalce number with n
        self.words = words[::-1]
        for i in self.words.strip():  # push into input stack
            self.input_stack.append(i)

    # algorithm 4.1 in page 89
    def run(self, table):
        print format('STACK', '<60'), format('INPUT MEMORY', '<60'), format('OUTPUT', '<15')
        while True:
            print format(self.stack, '<60'), format(self.input_stack, '<60'),
            x = self.stack[len(self.stack) - 1]
            a = self.input_stack[len(self.input_stack) - 1]
            if x in ['+', '-', '*', '/', '(', ')', 'n', '$']:
                if x == a:
                    self.stack.pop()
                    self.input_stack.pop()
                    print format('', '<15')
                else:
                    print 'Error!!!'
                    break
            else:
                if table[x][a] != 'error':
                    if table[x][a].split('>')[1] != 'epsilon':
                        self.stack.pop()
                        if 'E\'' in table[x][a]:
                            l = list(table[x][a].split('>')[1][::-1].strip())
                            l.remove('\'')
                            l.remove('E')
                            l.insert(0, 'E\'')
                        elif 'T\'' in table[x][a]:
                            l = list(table[x][a].split('>')[1][::-1].strip())
                            l.remove('\'')
                            l.remove('T')
                            l.insert(0, 'T\'')
                        else:
                            l = list(table[x][a].split('>')[1][::-1].strip())
                        for i in l:
                            self.stack.append(i)
                        print format(table[x][a], '<15')
                    else:
                        self.stack.pop()
                        print format(table[x][a], '<15')
                else:
                    print 'Error!!!'
                    break
            if x == '$':
                break

# python Controller.py target_string
if __name__ == "__main__":
    if len(sys.argv) == 2:
        words = sys.argv[1]
        controller = Controller(words.strip())
        Parser_Table = ParserTable.Table()
        Parser_Table.create_table()
        controller.run(Parser_Table.table)
