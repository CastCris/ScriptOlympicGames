# run

<u>focus on solving contest problems, not typing commands</u>

---

## NAME

**run** — focus on solving contest problems, not typing commands

---

## SYNOPSIS
**run -f** \<filename\> [options]

---

## DESCRIPTION

The **run** command is a shortcut to compile and/or execute solutions for programming contest problems.

It **helps reduce repetitive typing** and **simplifies file organization** by automatically handling execution details such as:

- language detection  
- input/output redirection  
- compilation or execution flags  

---

## OPTIONS

### **-f, --file** <filename>

<u>Specifies the source file containing the solution to be executed.</u>

---

### **-p, --path** <path>

<u>Specifies the absolute or relative path of the source file.</u>  
Useful when multiple files with the same name exist in a directory.

---

### **-l, --language** <language_name>

<u>Specifies the programming language explicitly.</u>  
If omitted, the language is automatically inferred from the file extension.

---

### **--flags** [flags...]

<u>Additional flags passed to the compiler or interpreter.</u>

---

### **-i, --input**

<u>Uses `input.txt` as the standard input.</u>

---

### **-o, --output**

<u>Redirects the program output to `output.txt`.</u>

---

### **-io**

<u>Equivalent to using both `--input` and `--output`.</u>
