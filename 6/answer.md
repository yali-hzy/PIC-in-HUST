## 第六讲作业
### 1 上下界包含的二分查找
```clike
int binsearch_inclusive(int x, int[ ] A, int n)
//@requires 0 <= n && n <= \length(A);
//@requires is_sorted(A, 0, n);
/*@ensures (-1 == \result && !is_in(x, A, 0, n))
       || ((0 <= \result && \result < n) && A[\result] == x);
  @*/
{
    int lower = 0;
    int upper = n - 1;
    while (lower <= upper)
    //@loop_invariant 0 <= lower && lower <= upper + 1 && upper < n;
    //@loop_invariant (lower == 0 || A[lower - 1] < x);
    //@loop_invariant (upper == n - 1 || A[upper + 1] > x);
    {
        int mid = lower + (upper - lower) / 2;
        //@assert lower <= mid && mid <= upper;
        if (A[mid] == x) return mid;
        else if (A[mid] < x) lower = mid + 1;
        else /*@assert(A[mid] > x);@*/
            upper = mid - 1;
    }
    //@assert upper + 1 == lower;
	return -1;
}
```

证明：

- 第 16 行 $lower\le mid\le upper$：用第 10, 11, 15 行和数学知识可证，由此可推出 $0\le mid<n$，下标合法

- 循环不变量

  - 初始情况：$lower=0,\ upper=n-1\ge-1$，（由第 2, 8, 9 行推出），成立

  - 假设循环不变量成立，证明下次循环时仍成立：
    $$
    0\le lower \le upper+1<n\\
    lower\le mid\le upper\\
    $$

    1. `A[mid] == x`：不进行判断，退出

    2. `A[mid] < x`：
       $$
       \begin{aligned}
       &lower' = mid+1\\
       &A[lower'-1]<x\ (Line\ 12\ 成立)\\
       &upper' = upper\ (Line\ 13\ 成立)\\
       &lower<mid+1\le upper+1\\
       &0\le lower< lower'\le upper'+1<n\ (Line\ 11\ 成立)\\
       \end{aligned}
       $$

    3. `A[mid] > x`：
       $$
       \begin{aligned}
       &upper' = mid-1\\
       &A[upper'+1]>x\ (Line\ 13\ 成立)\\
       &lower' = lower\ (Line\ 12\ 成立)\\
       &lower-1\le mid-1\\
       &0\le lower'\le upper'+1\le upper<n\ (Line\ 11\ 成立)
       \end{aligned}
       $$

  综上，循环不变量成立

- 循环可终止证明：

  记 $length = upper-lower+1$，则 

  - 若$upper' = mid-1,\ lower' = lower$，那么$length'=upper'-lower'+1=mid-lower<mid-lower+1\le upper-lower+1=length$
  - 若$upper' = upper,\ lower' = mid+1$，那么$length'=upper'-lower'+1=upper-mid<upper-mid+1\le upper-lower+1=length$

  所以 $length$ 严格单调递减，当 $length<1$ 时循环终止

- 后置条件证明：

  由于 `is_sorted(A,0,n)`，那么 $A[0,lower)<x$，$A[upper+1, n)>x$，当循环结束时，$lower>upper$，因此 $upper+1=lower$，$x\notin A[0,n)$

### 2 `is_in` 函数作循环不变量

```clike
int search(int x, int[] A, int n)
//@requires n == \length(A);
//@requires is_sorted(A, 0, n);
/*@ensures (\result == -1 && !is_in(x, A, 0, n)) 
        || (0 <= \result && \result < n && A[\result] == x); @*/
{
    int lower = 0;
    int upper = n;
    while (lower < upper)
    //@loop_invariant 0 <= lower && lower <= upper && upper <= n;
    //@loop_invariant !is_in(x, A, 0, lower);
    //@loop_invariant !is_in(x, A, upper, n);
    {
        int mid = lower + (upper - lower)/2;
        //@assert lower <= mid && mid < upper;
        if (A[mid] == x) return mid;
        if (A[mid] < x) {
            //@assert mid + 1 <= upper;
            //@assert !is_in(x, A, 0, mid + 1);
            lower = mid + 1;
        } else { //@assert A[mid] > x;
            //@assert !is_in(x, A, mid, n);
            upper = mid;
        }
    }
    //@assert lower == upper;
    //@assert !is_in(x, A, 0, n);
    return -1;
}
```

证明：

- 第 15 行 $lower\le mid< upper$：用第 9, 10, 14 行和数学知识可证，由此可推出 $0\le mid<n$，下标合法

- 第 18 行 `mid + 1 <= upper`，由 $mid<upper$ 推出

- 第 19 行，由于 `is_sorted(A, 0, n)` ，A单调上升，`A[mid] < x`，则 $A[0,mid+1)<x$，所以 `!is_in(x, A, 0, mid + 1)`

- 第 22 行，由于 `is_sorted(A, 0, n)` ，A单调上升，`A[mid] > x`，则 $A[mid,n)>x$，所以 `!is_in(x, A, mid, n)`

- 循环不变量

  - 初始情况：$lower=0,\ upper=n$，成立

  - 假设循环不变量成立，证明下次循环时仍成立：
    $$
    0\le lower \le upper\le n\\
    lower\le mid< upper\\
    $$

    1. `A[mid] == x`：不进行判断，退出

    2. `A[mid] < x`：仅 `lower` 改变，$lower'=mid+1$，由第 18 行 `mid + 1 <= upper`可知，第 10 行成立，由第 19 行 `!is_in(x, A, 0, mid + 1)` 可知，第 11 行成立

    3. `A[mid] > x`：仅 `upper` 改变，$upper'=mid$，由第 15 行 $lower\le mid<upper$ 可知，第 10 行成立，由第 22 行 `!is_in(x, A, mid, n)` 可知，第 12 行成立

  综上，循环不变量成立

- 循环可终止证明：

  记 $length = upper-lower$，则 

  - 若$upper' = mid,\ lower' = lower$，那么 $length'=upper'-lower'=mid-lower<upper-lower=length$
  - 若$upper' = upper,\ lower' = mid+1$，那么 $length'=upper'-lower'=upper-mid-1\le upper-lower-1<upper-lower=length$

  所以 $length$ 严格单调递减，当 $length\le0$ 时循环终止

- 第 26 行，由第 9, 10 行可知

- 后置条件证明：

  当 `\result != -1` 时是显然的。

  当 `\result == -1` 时，由第 11, 12, 26 行，`!is_in(x, A, 0, lower) && !is_in(x, A, upper, n) && lower == upper` 可以推出 `!is_in(x, A, 0, n)`

### 3 查找最左侧的x

- 例子：长度为5，全为1的数组，查找1，会返回2，而非0

```clike
int search(int x, int[] A, int n)
//@requires n == \length(A);
//@requires is_sorted(A, 0, n);
/*@ensures (\result == -1 && !is_in(x, A, 0, n)) 
        || (0 <= \result && \result < n && A[\result] == x && !is_in(x, A, 0, \result)); @*/
{
    int lower = 0;
    int upper = n;
    while (lower < upper)
    //@loop_invariant 0 <= lower && lower <= upper && upper <= n;
    //@loop_invariant (lower == 0 || A[lower - 1] < x);
    //@loop_invariant (upper == n || A[upper] >= x);
    {
        int mid = lower + (upper - lower)/2;
        //@assert lower <= mid && mid < upper;
        if (A[mid] < x) lower = mid + 1;
        else /*@assert A[mid] >= x; @*/
            upper = mid;
    }
    //@assert lower == upper;
    if (lower < n && A[lower] == x)
        return lower;
    return -1;
}
```

证明：

- 第 15 行 $lower\le mid< upper$：用第 9, 10, 14 行和数学知识可证，由此可推出 $0\le mid<n$，下标合法

- 循环不变量

  - 初始情况：$lower=0,\ upper=n$，成立

  - 假设循环不变量成立，证明下次循环时仍成立：
    $$
    0\le lower \le upper\le n\\
    lower\le mid< upper\\
    $$

    1. `A[mid] < x`：
       $$
       \begin{aligned}
       &lower' = mid+1\\
       &A[lower'-1]<x\ (Line\ 11\ 成立)\\
       &upper' = upper\ (Line\ 12\ 成立)\\
       &mid+1\le upper\\
       &0\le  lower'=mid+1\le upper = upper'\le n\ (Line\ 10\ 成立)\\
       \end{aligned}
       $$

    2. `A[mid] >= x`：
       $$
       \begin{aligned}
       &upper' = mid\\
       &A[upper']\ge x\ (Line\ 12\ 成立)\\
       &lower' = lower\ (Line\ 11\ 成立)\\
       &0\le lower'=lower\le mid=upper'\le n\ (Line\ 10\ 成立)
       \end{aligned}
       $$

  综上，循环不变量成立

- 循环可终止证明：

  记 $length = upper-lower$，则 

  - 若$upper' = mid,\ lower' = lower$，那么 $length'=upper'-lower'=mid-lower<upper-lower=length$
  - 若$upper' = upper,\ lower' = mid+1$，那么 $length'=upper'-lower'=upper-mid-1\le upper-lower-1<upper-lower=length$

  所以 $length$ 严格单调递减，当 $length\le0$ 时循环终止

- 第 20 行，由第 9, 10 行可知

- 后置条件证明：

  由于 `is_sorted(A,0,n)`，结合循环不变量，那么 $A[0,lower)<x$，$A[upper, n)\ge x$。当循环结束时，$lower=upper$，因此只需要验证 `A[lower]` 是否为 `x` 即可，同时，此处需注意验证下标合法。

### 4 整型溢出

如果改为 `int mid = (lower + upper)/2;`，那么在计算`lower + upper` 的时候可能会发生溢出，变为负数，最直接的是 `//@assert lower <= mid && mid < upper;` 会报错。而且，在访问 `A[mid]` 时，也会因为下标非法原因有异常产生。

### 5 死循环

- 证明循环不变量
  - 初始情况显然满足
  - 归纳的时候，由于 `lower` 和 `upper` 均未改变，所以在新一次循环中依然满足
- 假如初始时，$n>0$，那么循环无法终止，循环终止条件 $lower\ge upper$ 不可能满足
