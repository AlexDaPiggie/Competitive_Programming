×

#### Contest started

AtCoder Beginner Contest 453 has begun.

Close

×

#### Contest is over

AtCoder Beginner Contest 453 has ended.

Close

- [AtCoder Beginner Contest 453](https://atcoder.jp/contests/abc453)

- [![](https://img.atcoder.jp/assets/top/img/flag-lang/en.png) English](https://atcoder.jp/contests/abc453/tasks/abc453_f#)  - [![](https://img.atcoder.jp/assets/top/img/flag-lang/ja.png) 日本語](https://atcoder.jp/contests/abc453/tasks/abc453_f?lang=ja)
  - [![](https://img.atcoder.jp/assets/top/img/flag-lang/en.png) English](https://atcoder.jp/contests/abc453/tasks/abc453_f?lang=en)
- [Sign Up](https://atcoder.jp/register?continue=https%3A%2F%2Fatcoder.jp%2Fcontests%2Fabc453%2Ftasks%2Fabc453_f)
- [Sign In](https://atcoder.jp/login?continue=https%3A%2F%2Fatcoder.jp%2Fcontests%2Fabc453%2Ftasks%2Fabc453_f)


Contest Duration:
[2026-04-11(Sat) 08:00](http://www.timeanddate.com/worldclock/fixedtime.html?iso=20260411T2100&p1=248) \- [2026-04-11(Sat) 09:40](http://www.timeanddate.com/worldclock/fixedtime.html?iso=20260411T2240&p1=248) (local time)
(100 minutes)

[Back to Home](https://atcoder.jp/home)

- [Top](https://atcoder.jp/contests/abc453)
- [Tasks](https://atcoder.jp/contests/abc453/tasks)
- [Clarifications](https://atcoder.jp/contests/abc453/clarifications)
- [Results](https://atcoder.jp/contests/abc453/tasks/abc453_f#)  - [All Submissions](https://atcoder.jp/contests/abc453/submissions)
- [Standings](https://atcoder.jp/contests/abc453/standings)
- [Virtual Standings](https://atcoder.jp/contests/abc453/standings/virtual)
- [Editorial](https://atcoder.jp/contests/abc453/editorial)
- [Discuss](https://codeforces.com/blog/entry/152848)

F - Avoid Division
[Editorial](https://atcoder.jp/contests/abc453/tasks/abc453_f/editorial)![](https://img.atcoder.jp/assets/top/img/flag-lang/ja.png) / ![](https://img.atcoder.jp/assets/top/img/flag-lang/en.png)

* * *

Time Limit: 2 sec / Memory Limit: 1024 MiB




配点 : 550550550 点

### 問題文

NNN 頂点の木が与えられます。

頂点は頂点 111、頂点 222、…\\ldots…、頂点 NNN と番号づけられており、iii 番目 (1≤i≤N−1)(1\\leq i\\leq N-1)(1≤i≤N−1) の辺は頂点 UiU\_iUi​ と頂点 ViV\_iVi​ を結んでいます。

高橋君は各頂点を色 111、色 222、…\\ldots…、色 KKK のうちいずれか一色で塗ります。

色 iii は最大で CiC\_iCi​ 個の頂点を塗るのに使うことができます。

次の条件をみたすように頂点を塗ることが可能か判定し、可能な場合は条件をみたす塗り方を 111 つ出力してください。

- どの辺についても、ある iii(1≤i≤K)(1\\leq i\\leq K)(1≤i≤K) が存在して、その辺で木を切って得られる 222 つの部分木の両方に色 iii で塗られた頂点が存在する。

TTT 個のテストケースが与えられるので、それぞれについて答えを求めてください。

### 制約

- 1≤T≤1051\\leq T\\leq 10^51≤T≤105
- 2≤N≤3×1052\\leq N\\leq 3\\times 10^52≤N≤3×105
- 1≤K≤N1\\leq K\\leq N1≤K≤N
- 1≤Ui,Vi≤N1\\leq U\_i,V\_i\\leq N1≤Ui​,Vi​≤N
- 与えられるグラフは木である。
- 1≤Ci≤N1\\leq C\_i\\leq N1≤Ci​≤N
- C1+C2+⋯+CK≥NC\_1+C\_2+\\cdots+C\_K\\geq NC1​+C2​+⋯+CK​≥N
- 入力はすべて整数
- 各入力のテストケースにわたる NNN の総和は 3×1053\\times 10^53×105 を超えない。

* * *

### 入力

入力は以下の形式で標準入力から与えられる。

```
TTT
case1\mathrm{case}_1case1​
case2\mathrm{case}_2case2​
⋮\vdots⋮
caseT\mathrm{case}_TcaseT​
```

casei\\mathrm{case}\_icasei​ は iii 個目のテストケースを表す。

各テストケースは以下の形式で与えられる。

```
NNN KKK
U1U_1U1​ V1V_1V1​
U2U_2U2​ V2V_2V2​
⋮\vdots⋮
UN−1U_{N-1}UN−1​ VN−1V_{N-1}VN−1​
C1C_1C1​ C2C_2C2​ …\ldots… CKC_KCK​
```

### 出力

TTT 行出力せよ。

iii 行目 (1≤i≤T)(1\\leq i\\leq T)(1≤i≤T) には、iii 個目のテストケースに対する答えを以下のように出力せよ。

条件をみたすように頂点を塗ることが不可能ならば、−1-1−1 を 111 つだけ出力せよ。

そうでないならば、NNN 個の整数 X1,X2,…,XNX\_1,X\_2,\\ldots,X\_NX1​,X2​,…,XN​(1≤Xi≤K)(1\\leq X\_i\\leq K)(1≤Xi​≤K) を空白区切りで出力せよ。 ここで、j=1,2,…,Nj=1,2,\\ldots,Nj=1,2,…,N について頂点 iii を色 XiX\_iXi​ で塗った方法が条件をみたすようにせよ。

* * *

### 入力例 1Copy

Copy

```
2
5 3
1 2
1 3
2 4
2 5
2 2 2
3 3
1 2
2 3
1 1 1
```

### 出力例 1Copy

Copy

```
3 2 2 1 1
-1
```

111 個目のテストケースについて、出力例のように頂点を塗ったとします。

すなわち、頂点 111 に色 333 を、頂点 222 に色 222 を、頂点 333 に色 222 を、頂点 444 に色 111 を、頂点 555 に色 111 を塗ったとします。

このとき、頂点 111 と頂点 222 を結ぶ辺を切ったとすると、木は頂点 1,31,31,3 からなる部分木と頂点 2,4,52,4,52,4,5 からなる部分木に分かれますが、このときどちらにも色 222 で塗られた頂点（頂点 333 または頂点 222）が存在します。

与えられた木を他のどの辺で切ってもそのような色が存在するため、出力例の塗り方は条件をみたしています。

222 個目のテストケースについて、条件をみたすように頂点を塗る方法は存在しません。

Score : 550550550 points

### Problem Statement

You are given a tree with NNN vertices.

The vertices are numbered vertex 111, vertex 222, …\\ldots…, vertex NNN, and the iii-th edge (1≤i≤N−1)(1\\leq i\\leq N-1)(1≤i≤N−1) connects vertices UiU\_iUi​ and ViV\_iVi​.

Takahashi will color each vertex with one of colors 111, 222, …\\ldots…, KKK.

Color iii can be used to color at most CiC\_iCi​ vertices.

Determine whether it is possible to color the vertices satisfying the following condition, and if so, output one valid coloring.

- For every edge, there exists some iii(1≤i≤K)(1\\leq i\\leq K)(1≤i≤K) such that both of the two subtrees obtained by cutting the tree at that edge contain at least one vertex colored with color iii.

You are given TTT test cases; solve each of them.

### Constraints

- 1≤T≤1051\\leq T\\leq 10^51≤T≤105
- 2≤N≤3×1052\\leq N\\leq 3\\times 10^52≤N≤3×105
- 1≤K≤N1\\leq K\\leq N1≤K≤N
- 1≤Ui,Vi≤N1\\leq U\_i,V\_i\\leq N1≤Ui​,Vi​≤N
- The given graph is a tree.
- 1≤Ci≤N1\\leq C\_i\\leq N1≤Ci​≤N
- C1+C2+⋯+CK≥NC\_1+C\_2+\\cdots+C\_K\\geq NC1​+C2​+⋯+CK​≥N
- All input values are integers.
- The sum of NNN over all test cases does not exceed 3×1053\\times 10^53×105.

* * *

### Input

The input is given from Standard Input in the following format:

```
TTT
case1\mathrm{case}_1case1​
case2\mathrm{case}_2case2​
⋮\vdots⋮
caseT\mathrm{case}_TcaseT​
```

casei\\mathrm{case}\_icasei​ represents the iii-th test case.
Each test case is given in the following format:

```
NNN KKK
U1U_1U1​ V1V_1V1​
U2U_2U2​ V2V_2V2​
⋮\vdots⋮
UN−1U_{N-1}UN−1​ VN−1V_{N-1}VN−1​
C1C_1C1​ C2C_2C2​ …\ldots… CKC_KCK​
```

### Output

Output TTT lines.

On the iii-th line (1≤i≤T)(1\\leq i\\leq T)(1≤i≤T), output the answer for the iii-th test case as follows.

If it is impossible to color the vertices satisfying the condition, output −1-1−1 alone.

Otherwise, output NNN integers X1,X2,…,XNX\_1,X\_2,\\ldots,X\_NX1​,X2​,…,XN​(1≤Xi≤K)(1\\leq X\_i\\leq K)(1≤Xi​≤K) separated by spaces, such that coloring vertex iii with color XiX\_iXi​ for i=1,2,…,Ni=1,2,\\ldots,Ni=1,2,…,N satisfies the condition.

* * *

### Sample Input 1Copy

Copy

```
2
5 3
1 2
1 3
2 4
2 5
2 2 2
3 3
1 2
2 3
1 1 1
```

### Sample Output 1Copy

Copy

```
3 2 2 1 1
-1
```

For the first test case, suppose the vertices are colored as in the sample output.

That is, vertex 111 is colored with color 333, vertex 222 with color 222, vertex 333 with color 222, vertex 444 with color 111, and vertex 555 with color 111.

If we cut the edge connecting vertices 111 and 222, the tree splits into the subtree consisting of vertices 1,31,31,3 and the subtree consisting of vertices 2,4,52,4,52,4,5; both subtrees contain a vertex colored with color 222 (vertex 333 or vertex 222, respectively).

Such a color exists no matter which edge of the given tree is cut, so the coloring in the sample output satisfies the condition.

For the second test case, there is no valid coloring satisfying the condition.

* * *

[Facebook](https://atcoder.jp/#facebook) [Twitter](https://atcoder.jp/#twitter) [Telegram](https://atcoder.jp/#telegram) [Share](https://www.addtoany.com/share#url=https%3A%2F%2Fatcoder.jp%2Fcontests%2Fabc453%2Ftasks%2Fabc453_f%3Flang%3Den&title=F%20-%20Avoid%20Division)

* * *

- [Rule](https://atcoder.jp/contests/abc453/rules)
- [Glossary](https://atcoder.jp/contests/abc453/glossary)

- [Terms of service](https://atcoder.jp/tos)
- [Privacy Policy](https://atcoder.jp/privacy)
- [Information Protection Policy](https://atcoder.jp/personal)
- [Company](https://atcoder.jp/company)
- [FAQ](https://atcoder.jp/faq)
- [Contact](https://atcoder.jp/contact)

Copyright Since 2012 © [AtCoder Inc.](http://atcoder.co.jp/) All rights reserved.

2026-05-17 (Sun)

13:04:32 -04:00

Page Top

Copy link

✓

Thanks for sharing!

Find any service

[AddToAny](https://www.addtoany.com/ "Share Buttons")

[More…](https://atcoder.jp/contests/abc453/tasks/abc453_f#addtoany "Show all")

A2A