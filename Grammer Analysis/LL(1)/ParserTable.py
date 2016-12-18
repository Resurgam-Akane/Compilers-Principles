# coding=utf8
# ========================================================
#   Copyright (C) 2016 All rights reserved.
#
#   filename : ParserTable.py
#   author   : xuzhu / xuzhu1996@hotmail.com
#   date     : 2016-10-31
#   desc     : create a analysis table
# ========================================================

class Table:
    def __init__(self):
        self.first_set = {'E\'': ['+', '-', 'epsilon'], 'E': ['(', 'n'], 'T': ['(', 'n'], 'T\'': ['*', '/', 'epsilon'], 'F': ['(', 'n']}
        self.follow_set = {'E': ['$', ')'], 'E\'': ['$', ')'], 'T': ['+', '-', '$', ')'], 'T\'': ['+', '-', '$', ')'], 'F': ['+', '-', '*', '/', ')', '$']}
        self.rule = ['E->TE\'', 'E\'->+TE\'', 'E\'->-TE\'', 'E\'->epsilon', 'T->FT\'', 'T\'->*FT\'', 'T\'->/FT\'', 'T\'->epsilon', 'F->(E)', 'F->n']
        self.table = {'E': {}, 'E\'': {}, 'T': {}, 'T\'': {}, 'F': {}}

    # return FIRST(ch)
    def first(self, ch):
        if ch.isupper():
            return self.first_set[ch]
        elif ch == 'e':
            return ['epsilon']
        else:
            return ch

    # return FOLLOW(ch)
    def follow(self, ch):
        return self.follow_set[ch]

    # create analysis table
    # algorithm 4.2 in page 92
    def create_table(self):
        for generate_formula in self.rule:
            vn_symbol = generate_formula[0]
            if generate_formula[1] == '\'':  # if E' or T' in generate_formula
                vn_symbol += '\''

            for a in self.first(generate_formula[generate_formula.index('>')+1]):
                if a != 'epsilon':
                    self.table[vn_symbol].update({a: generate_formula})
            if 'epsilon' in self.first(generate_formula[generate_formula.index('>')+1]):
                for b in self.follow(vn_symbol):
                    self.table[vn_symbol].update({b: generate_formula})
        for vn_symbol in ['E', 'E\'', 'T', 'T\'', 'F']:
            for vt_symbol in [ i for i in ['+', '-', '*', '/', '(', ')', 'n', '$'] if i not in self.table[vn_symbol].keys()]:
                self.table[vn_symbol].update({vt_symbol: 'error'})

    # print table
    def show(self):
        print '\t',
        for a in ['+', '-', '*', '/', '(', ')', 'n', '$']:
            print format(a, '<15'),

        print '\n'

        for a in ['E', 'E\'', 'T', 'T\'', 'F']:
            print a + '\t',
            for b in ['+', '-', '*', '/', '(', ')', 'n', '$']:
                print format(self.table[a][b], '<15'),
            print '\n'



# python ParserTable.py
if __name__ == "__main__":
    table = Table()
    table.create_table()
    table.show()
