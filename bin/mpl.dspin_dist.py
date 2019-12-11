
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

DATA = [np.genfromtxt(i).tolist() for i in FILES] 
print("Number of halos: %d" % (sum([len(i) for i in DATA]))) 
for i in range(len(DATA)): 
	DATA[i] = list(filter(lambda x: x[1] == -1, DATA[i])) 
N = sum([len(i) for i in DATA]) 
print("Number of hosts: %d" % (N)) 

masses = N * [0] 
dspin_over_spin = N * [0] 
n = 0 
for i in DATA: 
	for j in i: 
		masses[n] = j[2] 
		dspin_over_spin = j[-1] / j[-2] 
		n += 1
data = [list(i) for i in zip(masses, dspin_over_spin)] 

def mass_filter(minlogm, maxlogm, nbins = 100): 
	return list(filter(lambda x: minlogm <= m.log10(x[0]) <= maxlogm, 
		data)) 

def setup_axis(): 
	fig = plt.figure(figsize = (7, 7)) 
	ax = fig.add_subplot(111, facecolor = "white") 
	ax.set_xlabel(r"$\Delta\lambda/\lambda$") 
	ax.set_ylabel("PDF") 
	return ax 

def get_dspin_distribution(mass_sub, nbins = 1000): 
	# bins = np.linspace(min([row[1] for row in mass_sub]), 
	# 	max([row[1] for row in mass_sub]), 
	# 	n_bins + 1) 
	return [i.tolist() for i in np.histogram([row[1] for row in mass_sub], 
		bins = nbins)] 

def get_dspin_rms(mass_sub): 
	return m.sqrt(np.mean([i**2 for i in [row[1] for row in mass_sub]])) 

def plot_dspin_distribution(ax, minlogm, maxlogm, color, nbins = 100): 
	mass_sub = mass_filter(minlogm, maxlogm, nbins = nbins) 
	hist, bins = get_dspin_distribution(mass_sub) 
	centers = list(map(lambda x, y: (x + y) / 2, bins[1:], bins[:-1])) 
	ax.plot(centers, hist, c = plots.mpltoolkit.named_colors()[color], 
		label = r"rms\($\Delta\lambda/\lambda\)$ = %.2e" % (
			get_dspin_rms(mass_sub))) 
	
if __name__ == "__main__": 
	plt.clf() 
	ax = setup_axis() 
	plot_dspin_distribution(ax, 11.9, 12.1, "crimson") 
	plot_dspin_distribution(ax, 12.9, 13.1, "lime") 
	plot_dspin_distribution(ax, 13.9, 14.1, "deepskyblue") 
	plot_dspin_distribution(ax, 1, 100, "black") 
	leg = ax.legend(loc = plots.mpltoolkit.mpl_loc("upper right"), ncol = 1, 
		frameon = False) 
	for i in leg.legendHandles: 
		i.set_visible(False) 
	plt.tight_layout() 
	plt.savefig("dspin_dist.pdf") 
	plt.clf() 
	

