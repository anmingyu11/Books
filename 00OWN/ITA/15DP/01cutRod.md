## 切钢条

动态规划是付出额外的内存控件来节省计算时间，是典型的时空权衡的例子。而时间上的节省是巨大的：可能将一个指数时间的解转化为一个多项式时间的解。如果子问题的数量是输入规模的多项式函数，而我们可以在多项式时间内求解出每个子问题，那么动态规划的总运行时间就是多项式阶的。

自顶向下
```
MEMOIZED-CUT-ROD(p,n)
let r[0..n]be a new array
for i = 0 to n
	r[i] = -INF
return MEMOIZED-CUT-ROD-AUX(p,n,r)

MEMOIZED-CUT-ROD-AUX(p,n,r)
if r[n] >= 0
	return r[n]
if n == 0
	q = 0
else 
	q = -INF
	for i = 1 to n
		q = max(q, p[i] + MEMOIZED-CUT-ROD-AUX(p,n-i,r))
r[n]=q
return q
```

自底向上
```
BOTTOM-UP-CUT-ROD(p,n)
let r[0..n] be a new array
r[0] = 0
for j = 1 to n
	q = -INF
	for i = 1 to j
		q = max(q,p[i] + r[j-i])
	r[j] = q
return r[n]
```

自底向上的动态规划处理子问题图中顶点的顺序为：对于一个给定的子问题x，在求解它之前求解邻接至它的子问题y。换句话说，对于任何子问题，直至它依赖的所有子问题已求解完成，才会求解它，

###重构解

