import re

class atom:
    def __init__(self):
        self.id = ''
        self.element = ''
        self.type = ''
        self.partial_charge = ''
        self.node_id = -1

class bond:
    def __init__(self):
        self.id = ''
        self.atoms = ('','')
        self.type = ''

class compound:
    def __init__(self):
        self.atoms = []
        self.bonds = []
        self.active = True

    def get_atom(self, atom_id):
        for atom in self.atoms:
            if atom.id == atom_id:
                return atom
        return None

    def print(self):
        atom_ind = 1
        bond_ind = 1
        string = ''
        if self.active:
            string = 'XP\n'
        else:
            string = 'XN\n'
        #do all of the atoms first
        for atom in self.atoms:
            string = string + 'v {} atom\n'.format(atom_ind)
            atom.node_id = atom_ind
            atom_ind += 1
            string = string + 'v {} {}\n'.format(atom_ind, atom.element)
            string = string +'u {} {} element\n'.format(atom_ind-1, atom_ind)
            atom_ind += 1
        #now do the bonds
        for bond in self.bonds:
            atom1 = bond.atoms[0]
            atom2 = bond.atoms[1]
            atom1_node = -1
            atom2_node = -1
            #get the node id of each atom
            for atom in self.atoms:
                if atom.id == atom1:
                    atom1_node = atom.node_id
                if atom.id == atom2:
                    atom2_node = atom.node_id
            if (atom1_node == -1):
                print('cannot find atom {}'.format(atom1))
            if (atom2_node == -1):
                print('cannot find atom {}'.format(atom2))
            string = string + 'u {} {} bond\n'.format(atom1_node, atom2_node)
        return string


active_ids = []
with open('activeIDs', 'r') as f:
    active_ids = [x.strip() for x in f]

inactive_ids = []
with open('inactiveIDs', 'r') as f:
    inactive_ids = [x.strip() for x in f]

compounds = {}

with open('atom_bond.pl', 'r') as f:
    for line in f:
        match = re.match('(atm|bond)\((.*)\).*', line)
        if match is not None:
            params = match.group(2).split(',')
            if params[0] not in compounds:
                compounds[params[0]] = compound()
                if params[0] in inactive_ids:
                    compounds[params[0]].active = False
            if match.group(1) == 'atm':
                curr_atom = atom()
                curr_atom.id = params[1]
                curr_atom.element = params[2]
                curr_atom.type = params[3]
                curr_atom.partial_charge = params[4]
                compounds[params[0]].atoms.append(curr_atom)
            elif match.group(1) == 'bond':
                curr_bond = bond()
                curr_bond.atoms = (params[1], params[2])
                curr_bond.type = params[3]
                compounds[params[0]].bonds.append(curr_bond)
            else:
                print('Unrecognized: {}'.format(params), end='')
                exit(0)

str_file = '%subdue version of th atom_bond file\n'
for comp in compounds:
    str_file = str_file + compounds[comp].print()

with open('atom_bond_subdue.g', 'w') as f:
    f.write(str_file)
