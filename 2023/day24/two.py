# Consider 3 random hailstones
# Rock position at t = (px + t*vx, py + t*vy, pz + t*vz)
# Hailstone 1 position at t1: (px1 + t1*vx1, py1 + t*vy1, pz1 + t*vz1)
# Hailstone 2 position at t2: (px2 + t2*vx2, py2 + t*vy2, pz2 + t*vz2)
# HailStone 3 position at t3: (px3 + t3*vx3, py3 + t*vy3, pz3 + t*vz3)

# The above info gives 9 equations and 9 unknowns
# Also know that px, py, pz, vx, vy, vz are integers
# Should be able to solve the equations.

# We know equations that describe the system, so we can plug these into Z3 to get the answer

from z3 import *

px = Int('px')
py = Int('py')
pz = Int('pz')
vx = Int('vx')
vy = Int('vy')
vz = Int('vz')
t1 = Int('t1')
t2 = Int('t2')
t3 = Int('t3')
t4 = Int('t4')
t5 = Int('t5')
t6 = Int('t6')

input_lines = open('input.txt').read().replace(" @", ",").splitlines()
px1, py1, pz1, vx1, vy1, vz1 = [int(x) for x in input_lines[0].split(",")]
px2, py2, pz2, vx2, vy2, vz2 = [int(x) for x in input_lines[1].split(",")]
px3, py3, pz3, vx3, vy3, vz3 = [int(x) for x in input_lines[2].split(",")]
px4, py4, pz4, vx4, vy4, vz4 = [int(x) for x in input_lines[3].split(",")]
px5, py5, pz5, vx5, vy5, vz5 = [int(x) for x in input_lines[4].split(",")]
px6, py6, pz6, vx6, vy6, vz6 = [int(x) for x in input_lines[5].split(",")]
# Tweek number of hailstones included to make Z3 solve faster

solver = Solver()
solver.add(px + t1*vx == px1 + t1*vx1)
solver.add(px + t2*vx == px2 + t2*vx2)
solver.add(px + t3*vx == px3 + t3*vx3)
solver.add(px + t4*vx == px4 + t4*vx4)
solver.add(px + t5*vx == px5 + t5*vx5)
solver.add(px + t6*vx == px6 + t6*vx6)

solver.add(py + t1*vy == py1 + t1*vy1)
solver.add(py + t2*vy == py2 + t2*vy2)
solver.add(py + t3*vy == py3 + t3*vy3)
solver.add(py + t4*vy == py4 + t4*vy4)
solver.add(py + t5*vy == py5 + t5*vy5)
solver.add(py + t6*vy == py6 + t6*vy6)

solver.add(pz + t1*vz == pz1 + t1*vz1)
solver.add(pz + t2*vz == pz2 + t2*vz2)
solver.add(pz + t3*vz == pz3 + t3*vz3)
solver.add(pz + t4*vz == pz4 + t4*vz4)
solver.add(pz + t5*vz == pz5 + t5*vz5)
solver.add(pz + t6*vz == pz6 + t6*vz6)



solver.check()
print(solver.model())

# [t2 = 495926101181,
#  t4 = 535880293419,
#  vx = 312,
#  py = 353939130278484,
#  t5 = 415555397791,
#  px = 129723668686742,
#  t1 = 379155208275,
#  vz = 109,
#  t3 = 731139771857,
#  vy = -116,
#  t6 = 395487489391,
#  pz = 227368817349775]


# [t2 = 495926101181,
#  t4 = 535880293419,
#  vx = 312,
#  py = 353939130278484,
#  t5 = 415555397791,
#  px = 129723668686742,
#  t1 = 379155208275,
#  vz = 109,
#  t3 = 731139771857,
#  vy = -116,
#  t6 = 395487489391,
#  pz = 227368817349775]


# Alternative solutions:
# Simple to understand geometric solution: https://www.reddit.com/r/adventofcode/comments/18qexvu/2023_day_24_part_2_3d_vector_interpretation_and/