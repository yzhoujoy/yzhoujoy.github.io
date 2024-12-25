---
layout: post
title:  "Linear Algebra Made Intuitive: Determinant and Eigenvalues"
tags: math
---

# Linear Algebra Made Intuitive: Determinant and Eigenvalues

## Introduction

Today, I came across the equation - the determiant of a matrix is equal to the product
of all its eigenvalues.
$$\det( A) \ =\ \prod _{i}( \lambda _{i}) \ \ \ \ \ \lambda _{i} \ =\ eig( A)$$

It got me thinking - why is this true? Sure, it can be
proven mathematically, but what's the intuition behind it?

In this blog, I'll try to explain the geometric intuition of determinants and eigenvalues,
exploring how they are connected and why this equation makes sense.

## Concepts

### Determinant

**Definition** - the determinant of a square matrix $A\in \mathbb{R}^{nxn}$,
noted $|A|\text{ or}\det (A)$ is expressed recursively in terms of $A_{\\i \\j}$,
which is the matrix A without $i^{th}\text{ row and } j^{th}\text{column}$, as the following: [\[1\]](#references)

$$\det( A) \ =\ \sum _{j=1}^{n}( -1)^{i+j} A_{i,j} |A_{\backslash i\backslash j} |$$

For example, to compute a 4x4 Matrix A, along the first row $i=1$

$$\begin{gathered}
\det( A) \ =\ det\left(\begin{matrix}
a1 & a2 & a3 & a4\\
b1 & b2 & b3 & b4\\
c1 & c2 & c3 & c4\\
d1 & d2 & d3 & d4
\end{matrix}\right) \ \\
=\ ( -1)^{1+1} *\ a1\ *\ \det\left(\begin{matrix}
b2 & b3 & b4\\
c2 & c3 & c4\\
d2 & d3 & c4
\end{matrix}\right) \ +\ ( -1)^{1+2} \ *\ a2\ *\ \det\left(\begin{matrix}
b1 & b3 & b4\\
c1 & c3 & c4\\
d1 & d3 & d4
\end{matrix}\right)\\
+\ ( -1)^{1+3} \ *\ a3\ *\ \det\left(\begin{matrix}
b1 & b2 & b4\\
c1 & c2 & c4\\
d1 & d2 & d4
\end{matrix}\right) \ +\ ( -1)^{1+4} \ *\ a4\ *\ \det\left(\begin{matrix}
b1 & b2 & b3\\
c1 & c2 & c3\\
d1 & d2 & d3
\end{matrix}\right)
\end{gathered}$$

Then, we can unwind a deteminant of a 3x3 matrix to determinants of 2x2 matrixes which can be further
unwind to determinants of scalers which are the scaler values themselves.

**Intuition** - Geometrically, the determinant of a matrix $A$ can be
interpreted as the scaling factor by which $A$ transforms a geometric shape that
spans all dimensions of the space.

For example, in 2D space, a unit square after aplying transformation
matrix $A$, the area is scaled by the determinant
$1*\ \det( A) \ =\ 1\ *\ ( ad\ -\ bc)$. It is easy to prove - subtracing the four triangle $A,B,C,D$ from the large rectangle $(a+c)(b+d)$.

![determinant](/images/2024-12-23-determinant-and-eigenvalues/determinant.png)

In 3D space, it reflects the scaling of a volume. [\[2\]](#references)


### Eigenvalue

**Definition** - Given a matrix $A\ \in \mathbb{R}^{nxn}$, $\lambda$ is an
eignenvalue of $A$ if there exist a non-zero vector
$v\ \in \ \mathbb{R}^{n}$, called eigenvector, such that we have:
$$Av\ =\ \lambda v$$

**Intuition** - A matrix can alter vectors' directions and magnitudes.
Eigenvectors are special vectors that the matrix only changes their magnitudes.
To be more precise, eigenvectors are the vectors that remain collinear (lie along the same line)
with their original directions after a matrix transformation. Therefore, an
eigenvalue can be interpreted as the factor by which the matrix scales
the space along its corresponding eigenvector.

For example, 2D space, after applying $A$,
- $v_{1} \ (1,0)$ is scaled by 2 along the same direction to $(2,0)$;
- $v_{2} (1,-1)$ is scaled by 1 along the same direction to $(1,-1)$;
- $v_{3} (1,0)$ is rotated 45 degree clock-wise and scaled by $\sqrt{2}$.

$v_{1}\text{and } v_{2}$ are eigenvectors since they remain collinear
with the original vectors. $v_{3}$ is not an eigenvector of $A$
since it not only scaled but also rotated (not collinear with the
original vector).

![eigenvector](/images/2024-12-23-determinant-and-eigenvalues/eigenvector.png)

If we can find a set of linear independent eigenvectors that span the
entire space, we can form a new basis, called eigenbasis. In practice,
we can often simplify complex matrix multiplications by transforming
vectors into the eigenbasis, where the matrix transformation reduces to simple scaling.

In the last example, we found $v_{1}( 2,\ 0) \ \text{and } v_{2} \ ( 1,\ -1)$ are two
eigenvectors of the matrix $A$. $v_{1}\text{and } v_{2}$ are linear-independent and
span the entire space, they form an eigenbasis.

In the eigenbasis, $v_{1}\text{and } v_{2}$ become the new basis vectors:
- $v_{1} \ ( 2,\ 0)$ becomes a basis vector $i'\ ( 1,\ 0)$
- $v_{2} \ ( 1,\ -1)$ becomes a basis vector $j'\ ( 0,\ 1)$.

Select a random point $p\ ( 4,\ 2)$ in the original basis and represent
it in the eigenbasis as $p'\ ( 3,\ -2)$. Applying $A$ on the original
basis point $p\ ( 4,\ 2)$ is equivalent to applying scaling along basis
vectors by corresponding eigenvalues on $p'\ ( 3,\ -2)$.

![eigenbasis](/images/2024-12-23-determinant-and-eigenvalues/eigenbasis.png)


Generalize to any vector $v$ in the original space, we have:
$$\begin{gathered}
A\ v\ =Eig\ ( \lambda \ *\ I) \ Eig^{-1} v\\
Eig^{-1} v\ -\ convert \ v\ to\ eigenbasis\ space\ v'\\
( \lambda \ *\ I) v'-\ scale\ along\ each\ eigenbasis\ with\ its\ eigenvalue\\
Eig\ ( \lambda \ *\ I) \ v'\ -\ converted\ v'\ back\ to\ the\ original\ basis
\end{gathered}$$

Imagine if we want to apply $A^{10}$ to a vector.
Instead of do 10 times full matrix multiplications, we can convert the vector
to the eigenbasis and appy with the diagonal matrix $\lambda ^{10} *I$.

## Why $\det (A)=\prod \lambda _{i}$

Now let's see what is the intuition behide this equation.

$\det (A)$ represents how a shape spanning all dimensions is scaled by the transformation $A$.
Each eigenvalue $\lambda _{i}$ denotes the scaling factor along a specific dimension.
$\prod \lambda _{i}$ reflects the overall impact of the transformation across all dimensions. 

Therefore, $\det (A)$ and $\prod \lambda _{i}$ describe the **same fundamental property** of the
matrix $A$.

**Mathematical proof**:

for all vector $v$ (check the previous section how we convert $v$
to the $v'$ eigenbasis, scale, and transfer it back to the original
basis.)

$$\begin{gathered}
Av\ =\ Eig( \lambda \ *\ I) Eig^{-1} v\\
\left( A\ -\ Eig( \lambda \ *\ I) Eig^{-1}\right) v\ =0\\
A\ =\ Eig( \lambda \ *\ I) \ Eig^{-1}\\
\det( A) \ =\ \det\left( Eig( \lambda \ *\ I) \ Eig^{-1}\right) \ =\ \det\left(( \lambda \ *\ I) \ Eig^{-1} Eig\right) \ =\ \det( \lambda \ *\ I) \ =\ \prod \lambda 
\end{gathered}$$

## Takeaways

In this blog, we explored several foundational concepts in
linear algebra: matrix determinants, eigenvalues (along with
eigenvectors and eigenbasis), and basis transformations.

We covered both the mathematical definitions and the intuitive
interpretations of these ideas.
- Determinant: reflect the scaling factor of the volume.
- Eigenvalue: describe the scaling factor along a specific dimension.
- Eigenbasis: represents vector in eigenbasis allows matrix operation to be simplified as scaling.
- Basis conversion: $P^{-1} APv$, $v$ is in $\mathbb{R}_{1}^{n}$, $P$ is the matrix to do
$\mathbb{R}_{1}^{n} \ \rightarrow \ \mathbb{R}_{2}^{n}$ , $A$ is the
operation we want to apply to $v'\ \in \ \mathbb{R}_{2}^{n}$ , $P^{-1}$
is the inverse of $P$. To apply $A$ to $v\ $, we first transfer is $v$
by $Pv$, apply $APv$, transfer back to $\mathbb{R}_{1}^{n}$ space
$P^{-1} APv$.

Finally, we discussed the elegant connection between determinants and eigenvalues:
$$\det (A)=\prod \lambda _{i}$$

## References
[1] : <https://stanford.edu/~shervine/teaching/cs-229/refresher-algebra-calculus>

[2] : <https://en.wikipedia.org/wiki/Determinant>

[3] : <https://www.youtube.com/watch?v=Ip3X9LOh2dk>
