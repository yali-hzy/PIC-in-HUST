# **Recitation 7**



## **Checkpoint 0**

$$
O(1)=O(4)\subset O(\log(\log(n)))\subset O(\log(n))\subset O(\log^2(n))\subset O(n)=O(4n+3)\\
\subset O(n\log(n))\subset O(n^2)=O(n^2+20000n+3)\subset O(2^n)\subset O(n!)
$$

## **Checkpoint 1**

记 $f(n)=n^3+300n^2$，$g(n)=n^3$，则 $\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=1$，可令 $c=2$，$n_0=301$，使得 $f(n)\le c* g(n)$成立

## **Checkpoint 2**

$\exist c, n_0, s.t.\forall n>n_0, f(n)\le c*g(n)$，又因为 $k>0$，则 $k*f(n)\le k*c*g(n)$，令 $c'=k*c>0$，$n_0'=n_0$，可使定义成立

