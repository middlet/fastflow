#!/usr/bin/env python

import random

def move_point(x,y):
	"""
	compute new coordinates for a point with a 4-nbrhood move
	"""
	d = random.randint(0, 4)
	dx, dy = random.randint(0, 5), random.randint(0, 5)
	if d==0:
		x += dx
	elif d==1:
		y += dy
	elif d==2:
		x -= dx
	elif d==3:
		y -= dy
	else:
		return None

	return (x,y)


def simulate(Np, Ni):
	"""
	simulate optical flow algorithm for Np points and Ni iterations
	"""
	points = [(random.randint(0,99), random.randint(0,99)) for pi in range(Np)]
	tracks = [[points[0]], [points[1]]]
	for ni in range(Ni):
		print 'iteration :',ni
		npoints = [None]*Np
		for ii, pi in enumerate(points):
			np = move_point(*pi)
			if np:
				npoints[ii] = np
		print '\t', points, npoints
		# append new points to existing tracks
		for ii in range(len(npoints)):
			oldp, newp = points[ii], npoints[ii]
			for ti, tt in enumerate(tracks):
				if oldp in tt:
					if newp:
						tracks[ti].append(newp)
		# 
		points = npoints
		for ii, pi in enumerate(points):
			if pi==None:
				points[ii] = (random.randint(0,99), random.randint(0,99))
				tracks.append([points[ii]])
	print 'tracks:'
	for ti, tt in enumerate(tracks):
		print ti,
		for pi in tt:
			print pi,
		print


if __name__ == '__main__':
	simulate(2, 5)