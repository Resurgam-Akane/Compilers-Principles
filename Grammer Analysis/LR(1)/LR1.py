# coding: utf-8
####################
#   name: 徐翥
#   student id:2014211285
#   class id: 2014211306
####################

import sys
import re

class LR1:
    def __init__(self, DFAfile = 'DFA.txt', Tablefile = 'Table.txt'):
        self.DFA = {}
        with open(DFAfile, 'r') as dfafile:
            item = 0
            for line in dfafile:
                text = line.strip()
                if text[0:4] == 'Item':
                    item = text.split(' ')[2]
                    self.DFA[item] = []
                else:
                    self.DFA[item].append(text)

        self.table = {}
        with open(Tablefile, 'r') as tablefile:
            for line in tablefile:
                text = line.strip()
                state = text.split('=>')[0].split(' ')[1].split(',')[0]
                input_symbol = text.split('=>')[0].split(' ')[2]
                action = text.split('=>')[1].strip()
                if state in self.table:
                    self.table[state][input_symbol] = action
                else:
                    self.table[state] = {input_symbol: action}

    def OutputDFA(self):
        for i in range(len(self.DFA)):
            print 'item ', str(i), 'is:'
            print self.DFA[str(i)]

    def OutputTable(self):
        for state in self.table:
            for input_symbol in self.table[state]:
                print '<state: ', state, 'input: ', input_symbol, '>: ', self.table[state][input_symbol]

    def LRAnalysis(self, line):
        stack = ['0']
        input_stack = ['$']
        num_list = re.findall(r"\d+\.?\d*", line)  # use regular expression to match number
        for i in num_list:
            line = line.replace(i, 'n')  # repalce number with n
        text = line[::-1]
        for i in text.strip():  # push into input stack
            input_stack.append(i)

        while True:
            print stack, '      ', input_stack, '      ',
            if self.table[stack[-1]][input_stack[-1]].split(' ')[0] == 'shift':

                stack.append(input_stack[-1])
                #print stack
                print 'shift  ', self.table[stack[-2]][input_stack[-1]].split(' ')[1]
                stack.append(self.table[stack[-2]][input_stack[-1]].split(' ')[1])
                input_stack.pop()
            elif self.table[stack[-1]][input_stack[-1]].split(' ')[0] == 'reduce':
                action = self.table[stack[-1]][input_stack[-1]].split(' ')[4:]
                A = self.table[stack[-1]][input_stack[-1]].split(' ')[2]
                for i in range(2*len(action)):
                    stack.pop()
                stack.append(A)
                stack.append(self.table[stack[-2]][A].split(' ')[1])
                print A, '->', action
            elif self.table[stack[-1]][input_stack[-1]].split(' ')[0] == 'acc':
                return True
            else:
                return False


if __name__ == "__main__":
    a = LR1()
    print 'The DFA is:'
    a.OutputDFA()

    print 'The table is:'
    a.OutputTable()

    with open('input.txt', 'r') as inputfile:
        print 'start analysis:'
        for line in inputfile:
            if line.strip() == '':
                continue
            elif a.LRAnalysis(line.strip()):
                print 'complete analysis this words'
                print ''
                print ''
            else:
                print 'the syntax cannot lead to this words'
                print ''
                print ''


