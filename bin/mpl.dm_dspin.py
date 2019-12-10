
import matplotlib.pyplot as plt 
import plots 
plots.mpltoolkit.load_mpl_presets()
import numpy as np 
import math as m
import sys 
import os 
DATA_DIR = "%sMultiDark/MDPL2/trees/" % (os.environ["DATA_DIRECTORY"]) 
FILES = ["%s%s" % (DATA_DIR, i) for i in os.listdir(DATA_DIR) if 
	i.endswith(".out")] 

# read in the data 
DATA = [np.genfromtxt(i).tolist() for i in FILES] 
print("Number of halos: %d" % (sum([len(i) for i in DATA]))) 
for i in range(len(DATA)): 
	DATA[i] = list(filter(lambda x: x[1] == -1, DATA[i])) 
N = sum([len(i) for i in DATA]) 
print("Number of hosts: %d" % (N)) 

# take the pieces we're interested in 
dm_over_m = N * [0] 
dspin_over_spin = N * [0] 
masses = N * [0] 
dcvir_over_cvir = N * [0] 
# dba_over_ba = N * [0] 
dca_over_ca = N * [0] 
n = 0
for i in DATA: 
	for j in i: 
		masses[n] = j[2] 
		dm_over_m[n] = j[3] / j[2] 
		dspin_over_spin[n] = j[-1] / j[-2] 
		dcvir_over_cvir[n] = j[5] / j[4] 
		try: 
			dca_over_ca[n] = j[9] / j[8] 
		except ZeroDivisionError: 
			dca_over_ca[n] = float("nan") 
		n += 1
data = [list(i) for i in zip(masses, dm_over_m, dspin_over_spin, 
	dcvir_over_cvir, dca_over_ca)] 


def generate_ordered_subsamples(data, n, xcol): 
	indeces = np.argsort([row[xcol] for row in data]).tolist() 
	data = [data[i] for i in indeces] 
	x = int(len(data) / n) 
	subs = n * [None] 
	for i in range(n): 
		subs[i] = data[(x * i) : (x * (i + 1))] 
	return subs 


def variance(arr, x = 0.68): 
	arr = np.sort(arr) 
	start = int(m.floor((0.5 - x / 2) * len(arr))) 
	stop = int(m.ceil((0.5 + x / 2) * len(arr))) 
	return [arr[start], arr[stop]] 


def analyze(sub, xcol): 
	med_dx = np.median([row[xcol] for row in sub])
	med_dspin = np.median([row[2] for row in sub]) 
	yerr = variance([row[2] for row in sub]) 
	return [med_dx, med_dspin, yerr[0], yerr[1]] 


def mass_range(data, minlogm, maxlogm, xcol, nbins = 100): 
	filtered = list(filter(lambda x: minlogm <= m.log10(x[0]) <= maxlogm, 
		data)) 
	ordered = generate_ordered_subsamples(filtered, nbins, xcol) 
	x = len(ordered) * [0] 
	y = len(ordered) * [0] 
	low = len(ordered) * [0] 
	high = len(ordered) * [0] 
	for i in range(len(ordered)): 
		x[i], y[i], low[i], high[i] = analyze(ordered[i], xcol) 
	return [x, y, low, high] 


def setup_axes(): 
	fig = plt.figure(figsize = (21, 7)) 
	xlabels = [r"$\Delta M_\text{vir}/M_\text{vir}$", 
		r"$\Delta c_\text{vir}/c_\text{vir}$", 
		r"$\Delta(c/a)/(c/a)$"] 
	xlim = [[-0.12, 0.24], [-0.65, 0.25], [-0.65, 0.15]] 
	ylim = [-0.8, 0.8] 
	axes = 3 * [None] 
	for i in range(len(axes)): 
		axes[i] = fig.add_subplot(131 + i, facecolor = "white") 
		axes[i].set_xlabel(xlabels[i]) 
		axes[i].set_xlim(xlim[i]) 
		axes[i].set_ylim(ylim) 
		axes[i].plot(xlim[i], 2 * [0], linestyle = ':', 
			c = plots.mpltoolkit.named_colors()["black"]) 
		axes[i].plot(2 * [0], ylim, linestyle = ':', 
			c = plots.mpltoolkit.named_colors()["black"]) 
	axes[0].set_ylabel(r"$\Delta\lambda/\lambda$") 
	for i in range(1, len(axes)): 
		plt.setp(axes[i].get_yticklabels(), visible = False) 
	return axes 


def plot_relation(ax, x, y, low, high, color): 
	ax.plot(x, y, c = plots.mpltoolkit.named_colors()[color]) 
	ax.plot(x, low, c = plots.mpltoolkit.named_colors()[color], 
		linestyle = '--') 
	ax.plot(x, high, c = plots.mpltoolkit.named_colors()[color], 
		linestyle = '--') 


def legend(ax, colors, labels): 
	lines = len(colors) * [None] 
	for i in range(len(colors)): 
		lines[i] = ax.plot([0, 0.1], [0, 0.1], label = labels[i], 
			c = plots.mpltoolkit.named_colors()["white"])[0] 
	leg = ax.legend(loc = plots.mpltoolkit.mpl_loc("lower left"), ncol = 1, 
		frameon = False, handlelength = 0, fontsize = 25) 
	for i in range(len(lines)): 
		lines[i].remove() 
		leg.get_texts()[i].set_color(colors[i]) 


if __name__ == "__main__": 
	plt.clf() 
	axes = setup_axes() 
	colors = ["crimson", "lime", "dodgerblue", "black"] 
	labels = [r"$10^{12\pm0.1}\ h^{-1}\ M_\odot$", 
			r"$10^{13\pm0.1}\ h^{-1}\ M_\odot$", 
			r"$10^{14\pm0.1}\ h^{-1}\ M_\odot$", 
			"All Haloes"] 
	for i in range(4): 
		if i == 2: 
			nbins = 50 
		else: 
			nbins = 100 
		x, y, low, high = mass_range(data, [11.9, 12.9, 13.9, 1][i], 
			[12.1, 13.1, 14.1, 100][i], 1, nbins = nbins) 
		plot_relation(axes[0], x, y, low, high, colors[i]) 
		x, y, low, high = mass_range(data, [11.9, 12.9, 13.9, 1][i], 
			[12.1, 13.1, 14.1, 100][i], 3, nbins = nbins) 
		plot_relation(axes[1], x, y, low, high, colors[i])
		x, y, low, high = mass_range(data, [11.9, 12.9, 13.9, 1][i], 
			[12.1, 13.1, 14.1, 100][i], 4, nbins = nbins) 
		plot_relation(axes[2], x, y, low, high, colors[i]) 
	legend(axes[1], colors, labels) 
	plt.tight_layout() 
	plt.subplots_adjust(wspace = 0) 
	plt.savefig("dm_dspin.pdf") 
	plt.clf() 


# if __name__ == "__main__": 
# 	fig = plt.figure(figsize= (7, 7)) 
# 	ax = fig.add_subplot(111, facecolor = "white") 
# 	ax.set_xlabel(r"$\Delta M / M$") 
# 	ax.set_ylabel(r"$\Delta\lambda/\lambda$") 
# 	# ax.set_xlim([-0.12, 0.22]) 
# 	# ax.set_ylim([-0.8, 0.8]) 
# 	# ax.yaxis.set_ticks(np.linspace(-0.8, 0.8, 9)) 
# 	colors = ["crimson", "lime", "dodgerblue", "black"] 
# 	labels = [r"$10^{12\pm0.1}\ h^{-1}\ M_\odot$", 
# 			r"$10^{13\pm0.1}\ h^{-1}\ M_\odot$", 
# 			r"$10^{14\pm0.1}\ h^{-1}\ M_\odot$", 
# 			"All Haloes"]
# 	for i in range(len(colors)): 
# 		if i == 2: 
# 			nbins = 50 
# 		else: 
# 			nbins = 100 
# 		x, y, low, high = mass_range(data, [11.9, 12.9, 13.9, 1][i], 
# 			[12.1, 13.1, 14.1, 100][i], nbins = nbins)  
# 		ax.plot(x, y, c = plots.mpltoolkit.named_colors()[colors[i]], 
# 			label = labels[i])  
# 		ax.plot(x, low, c = plots.mpltoolkit.named_colors()[colors[i]], 
# 			linestyle = '--') 
# 		ax.plot(x, high, c = plots.mpltoolkit.named_colors()[colors[i]], 
# 			linestyle = '--') 
# 	ax.plot(ax.get_xlim(), 2 * [0], 
# 		c = plots.mpltoolkit.named_colors()["black"], linestyle = ':') 
# 	ax.plot(ax.get_xlim(), 2 * [0.1], 
# 		c = plots.mpltoolkit.named_colors()["black"], linestyle = ':') 
# 	ax.plot(2 * [0], ax.get_ylim(), 
# 		c = plots.mpltoolkit.named_colors()["black"], linestyle = ':') 
# 	leg = ax.legend(loc = plots.mpltoolkit.mpl_loc("lower right"), ncol = 1, 
# 		frameon = False, handlelength = 0, fontsize = 20) 
# 	for i in range(4): 
# 		leg.get_texts()[i].set_color(colors[i]) 
# 	plt.tight_layout() 
# 	plt.savefig("dm_dspin.pdf") 
