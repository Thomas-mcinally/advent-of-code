from collections import defaultdict


label_to_wire = defaultdict(lambda: Wire())

class Wire:
    def __init__(self):
        self.val = None
        self.dependent_gates: list[LogicGate] = []
    
    def set_val(self, val):
        self.val = val
        for gate in self.dependent_gates:
            if not gate.is_ready(): continue
            output_wire = gate.output_wire
            output_wire.set_val(gate.evaluate_inputs())


class LogicGate:
    def __init__(self, input_wires: list[Wire], output_wire: Wire, operation: str) -> None:
        self.input_wires = input_wires
        self.output_wire = output_wire
        self.operation = operation
    
    @classmethod
    def create_from_string(cls, input_string: str):
        global label_to_wire
        operation = None
        if "XOR" in input_string:
            operation = "^"
        elif "AND" in input_string:
            operation = "&"
        elif "OR" in input_string:
            operation = "|"
        
        components = input_string.split(" ")
        output = components[-1]
        output_wire = label_to_wire[output]
        inputs = [components[0], components[2]]
        input_wires = [label_to_wire[label] for label in inputs]

        return cls(input_wires=input_wires, output_wire=output_wire, operation=operation)
    
    def is_ready(self):
        return all(wire.val is not None for wire in self.input_wires)

    def evaluate_inputs(self):
        if not self.is_ready():
            raise
        return eval(f"{self.input_wires[0].val} {self.operation} {self.input_wires[1].val}")

def get_val(prefix):
    result = 0
    for label, wire in label_to_wire.items():
        if label[0] != prefix:
            continue
        result += (wire.val<<int(label[1:]))
    return result


with open("input.txt") as f:
    s = f.read().strip()
sections = s.split("\n\n")
for line in sections[1].splitlines():
    new_gate = LogicGate.create_from_string(line)
    for wire in new_gate.input_wires:
        wire.dependent_gates.append(new_gate)
for line in sections[0].splitlines():
    label, val = line.split(": ")
    label_to_wire[label].set_val(int(val))

print(get_val("z"))
