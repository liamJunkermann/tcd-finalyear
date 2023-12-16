Links: [[Histograms]]
Tags:
___
# Histogram Comparison Methods

- $D_{correlation} (h_1, h_2) = \frac{\sum_i (h_1(i)-\bar h_1)(h_2(i)-\bar h_2)}{\sqrt{\sum_i(h_1(i)-\bar h_1)^2(h_2(i)-\bar h_2)^2}}$
- $D_{Chi-Square}(h_1, h_2) = \sum_{i}{\frac{(h_1(i)-h_2(i))^2}{(h_1(i)+h_2(i))}}$
- $D_{intersection}(h1,h2) = \sum_i min(h_1(i),h_2(i))$
- $D_{Bahattacharyya}(h_1,h_2)=\sqrt{1-\frac{1}{\sqrt{\bar{h_1}\times\bar{h_2}\times N^2}}}\sum_i\sqrt{h_1(i)\times h_2(i)}$


___
Created: 2023-12-11

