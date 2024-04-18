A user can supply data both as a function of energy and wavelength. You can test the result by looking the printed output of material properties table. The output should be the same.

1- if you want to supply data as a function of energy, you should use the below macro command:
/matPropTable/water/addProperty ABSLENGTH data/matPropTable/water/absLength.txt eV m
absLength.txt   -->> supplied discrete energy-value data. energy unit is eV and absLength unit is meter

2- if you want to supply data as a function of wavelength, you should use the below macro command.
/matPropTable/water/addProperty ABSLENGTH data/matPropTable/water/absLength1.txt nm m 
absLength1.txt  -->> supplied discrete wavelength-value data. wavelength unit is nm and absLength unit is meter


3-Also, the data provided does not need to be in ascending or descending order.
