# Price-Estimator
This program uses a matrix multiplication to find the weights required to estimate price of a house given data.
This program uses a technique called one-shot machine learning. This program finds the weights of the of the given x and the final y attributes of the data.
It implements the Gaussian Jordan Elimination to compute (XT X)^-1 XTY to calculate the vector weight W.

Notes: Some testcases that I used to calculate the weights resulted in nonsense values (inf,-nan), however the majority of testcases (such as the ones posted on this repository) work.

