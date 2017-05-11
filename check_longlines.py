#!/usr/bin/python2

import sys, re, os

LINE=64
FIRST_PAGE=91
PAGE=93

NO_TEAMBOOK = re.compile(".*NO.TEAMBOOK.*")
NO_LONLINES = re.compile(".*NO.LONGLINES_CHECK.*")
BEGIN_CODE = re.compile(".*BEGIN.CODE.*")
END_CODE = re.compile(".*END.CODE.*")

def check_file(filename):
    lines = map(str.rstrip, open(filename).readlines())

    if any(NO_TEAMBOOK.match(line) for line in lines):
        return False
    if any(NO_LONLINES.match(line) for line in lines):
        return False

    if any(BEGIN_CODE.match(line) for line in lines):
        need_code = False
        code = []
        for i in range(len(lines)):
            line = lines[i]
            if END_CODE.match(line):
                need_code = False
            elif BEGIN_CODE.match(line):
                need_code = True
            elif need_code:
                code.append([i + 1, line])
    else:
        code = zip(range(1, len(lines) + 1), lines)
    lines = code

    fixable = [] # rem <= 5
    bad = []
    lineno = 0

    for i in range(len(lines)):
        l = len(lines[i][1].decode("utf8"))
        if l > LINE + 5:
            bad += [(i + 1, lines[i][0], l - LINE)]
        elif l > LINE:
            fixable += [(i + 1, lines[i][0], l - LINE)]
        if l == 0:
            l = 1
        lineno += (l + LINE - 1) / LINE 

    extra_lines = 0
    if lineno <= FIRST_PAGE:
        pass
    else:
        lineno -= FIRST_PAGE
        if lineno % PAGE <= 10:
            extra_lines = lineno % PAGE

    if not (fixable or bad or extra_lines):
        return False

    print "Errors for file '%s'" % filename
    if fixable:
        errors = True
        print "Fixable errors:"
        for x in fixable:
            print " Line %d (%d): %d extra symbol(s)" % x
    if bad:
        errors = True
        print "Large errors:"
        for x in bad:
            print " Line %d (%d): %d extra symbol(s)" % x
    if extra_lines:
        print "%d extra line(s)" % extra_lines
    print

    return True

total_errors = 0

for entry in os.walk("algo"):
    for filename in entry[2]:
        if not filename.endswith(".cpp") and not filename.endswith(".py"):
            continue
        fullname = os.path.join(entry[0], filename)
        if check_file(fullname):
            total_errors += 1
print "%d erronic file(s) found" % total_errors
