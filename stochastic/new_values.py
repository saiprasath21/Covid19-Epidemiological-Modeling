import pandas as pd
data = pd.read_excel("nz-calibration.ods", engine="odf")

new_values = data['Real']

print(new_values)


for i in new_values:
	print(str(i)+", ",end="")