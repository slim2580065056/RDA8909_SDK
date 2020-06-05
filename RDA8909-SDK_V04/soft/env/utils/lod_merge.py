#!/usr/bin/python

import os, sys
import re
import optparse

try:
    dict.iteritems
except AttributeError:
    def itervalues(d):
        return iter(d.values())
    def iteritems(d):
        return iter(d.items())
else:
    def itervalues(d):
        return d.itervalues()
    def iteritems(d):
        return d.iteritems()

class LOD(object):

    def __init__(self):
        self.attrnames = []
        self.attrs = {}
        self.blocks = {}

    def load(self, fname):
        try:
            fh = open(fname, 'r')
        except:
            print("failed to open %s for read" % fname)
            return False

        self.attrnames = []
        self.attrs = {}
        self.blocks = {}

        lineno = 0
        block_base_re = re.compile("@([0-9A-Fa-f]{8})")
        block_data_re = re.compile("^([0-9A-Fa-f]{8})")
        block_base = None
        block_data = []
        for line in fh.readlines():
            lineno += 1
            if line.startswith("#$"):
                fields = line[2:].strip().split("=")
                if len(fields) != 2:
                    print("LOD syntax error at %s:%d" %(fname, lineno))
                    fh.close()
                    return False
                self.attrnames.append(fields[0])
                self.attrs[fields[0]] = fields[1]
            elif line.startswith("#checksum="):
                pass
            elif line.startswith("@"):
                m = block_base_re.search(line)
                if m is None:
                    print("LOD syntax error at %s:%d" %(fname, lineno))
                    fh.close()
                    return False
                if block_base is not None:
                    self.blocks[block_base] = block_data
                    block_base = None
                    block_data = []
                block_base = int(m.group(1), 16)
            else:
                m = block_data_re.search(line)
                if m is None or block_base is None:
                    print("LOD syntax error at %s:%d" %(fname, lineno))
                    fh.close()
                    return False
                block_data.append(int(m.group(1), 16))

        # in case there are no checksum
        if block_base is not None:
            self.blocks[block_base] = block_data
            block_base = None
            block_data = []

        fh.close()
        return True

    def store(self, fname):
        try:
            fh = open(fname, 'w')
        except:
            print("failed to open %s for write" % fname)
            return False

        for attr in self.attrnames:
            fh.write("#$%s=%s\n" %(attr, self.attrs[attr]))
        for block_base in sorted(self.blocks.keys()):
            fh.write("@%08x\n" % block_base)
            for data in self.blocks[block_base]:
                fh.write("%08x\n" % data)
        fh.close()
        return True

    def end_address(self):
        ea = 0
        for block_base, block_data in iteritems(self.blocks):
            bea = block_base + len(block_data) *4
            if bea > ea:
                ea = bea
        return ea

    def start_address(self):
        return sorted(self.blocks.keys())[0]

def load_lod(fname):
    lod = LOD()
    if lod.load(fname):
        return lod
    return None

def merge_lod(lod1, lod2):
    sa1 = lod1.start_address()
    sa2 = lod2.start_address()
    if sa1 > sa2:
        sa1, sa2 = sa2, sa1
        lod1, lod2 = lod2, lod1

    for key in lod1.blocks:
        if key in lod2.blocks:
            print('Address overlapped at %08x' % key)
            return None

    bs1 = None
    bs2 = None
    if 'BOOT_SECTOR' in lod1.attrnames:
        bs1 = int(lod1.attrs['BOOT_SECTOR'], 0) | 0x08000000
        if bs1 != sa1:
            print('BOOT_SECTOR of the first lod is not at the start address')
            return None
    if 'BOOT_SECTOR' in lod2.attrnames:
        bs2 = int(lod2.attrs['BOOT_SECTOR'], 0) | 0x08000000
        if bs2 != sa2:
            print('BOOT_SECTOR of the second lod is not at the start address')
            return None

    output = LOD()
    output.blocks = lod2.blocks
    if bs2 != None:
        output.blocks[bs2][0] = 0xD9EF0045
    if bs1 != None:
        output.attrnames = lod1.attrnames
        for attr in output.attrnames:
            output.attrs[attr] = lod1.attrs[attr]
        output.attrs['BOOT_SECTOR'] = lod1.attrs['BOOT_SECTOR']
    output.blocks.update(lod1.blocks)

    out_keys = sorted(output.blocks.keys())
    lastaddr = out_keys[0] + len(output.blocks[out_keys[0]]) * 4
    for key in out_keys[1:]:
        if lastaddr > key:
            print("Data overlapped at %08x" % key)
            return None
        else:
            lastaddr = key + len(output.blocks[key]) * 4
    return output

def main(argv):
    opt = optparse.OptionParser(usage="""%prog [options]

    This utility will merge LODs into one. During merge:
    * Check `BOOT_SECTOR` for each LOD;
    * If the LOD with the minimum address has no BOOT_SECTOR, neither do the
      output LOD. Else `BOOT_SECTOR` of the output will follow this LOD;
    * First word of the non-minimum address which has `BOOT_SECTOR` will be
      changed to magic number;
    """)
    opt.add_option('--input', action='append', dest='input',
                   help='all LOD file names')
    opt.add_option('--output', action='store', dest='output',
                   help='output LOD file name')

    opt, argv = opt.parse_args(argv)
    if opt.input is None:
        print('No input LOD file.')
        return 1
    if opt.output is None:
        print('Output LOD file name is not specified')
        return 1
    lods = [load_lod(l) for l in opt.input]
    if len(lods) < 2:
        print('Less than 2 lods, do not need to merge')
        return 1
    if None in lods:
        print('At least one of input file is invalid.')
        return 1

    output = lods[0]
    for l in lods[1:]:
        output = merge_lod(output, l)
    if output is None:
        return 1
    if not output.store(opt.output):
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
