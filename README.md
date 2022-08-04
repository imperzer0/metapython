# METAPYTHON

<i>metaprogramming extension for python programming language</i>

## General explanation

It's just an application that generates python code from metapython code.
Metapython programming language has the same syntax as python.
But it has a feature of code segment preprocessing.

It looks like this
```python
result=@@@
def __metagenerator__():
    return 122+23
@@@
print(result)
```

If you compile the code above you'll get
```python
result=145
print(result)
```

Metapython gets the code between ```@@@```, executes it during
compilation and places the result instead of it.

## The syntax

The syntax of metacode segment is the same as python's, except
it requires ```__metagenerator__``` token to obtain the execution
result.

It could be a function that returns the result or a variable that
stores the result.

If the result is a string, compiler will substitute it directly
(without the quotes).
Otherwise, it will convert it into string and then substitute.

## Examples

```python
result = @@@
def __metagenerator__():
    return "\"the result will be a string\""
@@@
```
Turns into
```python
result = "the result will be a string"
```

<br/>

```python
result = @@@__metagenerator__="122"+"150"@@@
```
Turns into
```python
result = 122150
```

<br/>

```python
result = @@@__metagenerator__=(1, 2, 4, 5)@@@
```
Turns into
```python
result = (1, 2, 4, 5)
```

## Installation

### From AUR (Arch-based distros)

```bash
yay -Sy metapython
```

### From Git repository

```bash
git clone https://github.com/imperzer0/metapython.git
cd metapython
```

#### Archlinux
```bash
makepkg -sif
```

#### Other distributions
```bash
sudo bash -c ". ./PKGBUILD && build && notarch_package"
```
