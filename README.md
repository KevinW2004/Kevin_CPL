# Kevin_CPL
>2022 fall 大一上学期  

<br>

# NOTES
## 输入输出
1. %xx.xf 默认右对齐,  %-xx.xf 左对齐
2. %.xg 保留x位`有效数字`,科学计数法输出(%.xe 保留x位`小数`,科学计数法)
3. **scanf读取double要加上“l”（小写L）修饰符！！！！！！！！！！！！！**
4. pow的底数只能为正数
5. 开立方（包括正负）可以用cbrt（）s
6. fgets(str, length, stdin);

## 头文件包含关系
1. pow()在<math.h>
2. <ctype.h>:toupper()转大写, tolower转小写
   
## 循环、分支
1. for内部定义的int i在出循环之后会消失

## 算法
1. 二叉堆（不使用0号位）中位置k的父结点在[k/2],子结点在2k和2k+1

## 来自互联网
1. 
```
"C_Cpp.clang_format_style": "{ BasedOnStyle: Chromium, IndentWidth: 4},"
```
取消vsc自动格式左大括号会自动换行   

2. 更改一行的换行长度
```
   "editor.wordWrap": "wordWrapColumn",
    "editor.wordWrapColumn": 120,
```  

# UC Online Courses
1. editor:sublime (linux), command: subl file 
