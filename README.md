# AssemScript
 > Assembly-like and pointer based programming language

```c
#asset 0 "Hello, World!" // Save the asset "Hello, World" to 0th Asset Store

// get Asset
MOV -1 // move to first argument
VAL 0 // set the argument "strFrom" to 0

MOV -2 // move to second argument
VAL 0 // set the argument "dst" to 0, so getAsset function will copy the asset to 0th

MOV 0 // Set position to Calling Pointer
VAL 2 // set calling id to 002(getAsset)
CAL // Copy asset


// execute writeStr()
MOV -1 // move to first argument
VAL 0 // set the argument "strFrom" to 0

MOV 0 // Set position to Calling Pointer
VAL 101 // set calling id to 101(writeStr)
CAL // print string
```

```
$ asc --file HelloWorld.asc

Hello, World!
---- AssemScript Finished (16ms) ----
```

## 개요
현재 계획중인 언어입니다

## 포인터
### 상용 포인터
 * 범위 : 양수

실제 프로그램에서 사용되는 포인터입니다.

### 라이브러리 포인터
 * 범위 : 0

라이브러리를 실행하기 위한 `라이브러리 코드`를 가리키는 포인터입니다.   
라이브러리 명세서는 `라이브러리` 문단을 참고하세요.

### 인자 포인터
 * 범위 : 음수

라이브러리를 실행할 때 넘겨줄 인자값을 가리키는 포인터입니다.   
1번째 인자는 -1번째 위치에, 2번째 인자는 -2번째 위치에 접근하여 지정해야 합니다.

## 명령어
### MOV
Usage :
```
MOV 위치/nxt/prv
```
포인터 위치를 이동하는 명령어입니다.   

**인자 :**
 * 위치 : 이동할 위치
 * nxt : 현재 위치로부터 다음 위치
 * prv : 현재 위치로부터 이전 위치


### RPT
Usage :
```
RPT 위치/cur {
  코드 블록
}
```
조건에 있는 포인터가 가리키는 값이 0이 될 때까지 `코드 블록`을 반복합니다.

**인자 :**
 * 위치 : 조건 위치(변하지 않음)
 * cur : 현재 위치(포인터를 이동 시, 이동된 포인터가 조건으로 바뀜)

### CAL
Usage :
```
CAL
```
`라이브러리 포인터`에 지정된 라이브러리를 실행합니다.

### VAL
Usage :
```
VAL 값/++/--
```
현재 포인터가 가리키는 값을 수정합니다.
**인자 :**
 * 값 : 해당 값으로 설정
 * ++ : 현재 값에서 1bit 더함
 * -- : 현재 값에서 1bit 뺌

## 라이브러리
### 0번대(Basic Functions)
 0. N/A
 1. `copyTo(from, dst)`
 2. `getAsset(id, dst)`

### 100번대(Standard I/O)
 0. `write(ascii)` : 인자값에 해당하는 위치의 값을 UTF-8 형식으로 출력합니다.
 1. `writeStr(strFrom)` : 인자값에 해당하는 위치로부터 `\0` 문자가 나올 때까지 계속 UTF-8 형식으로 출력합니다.
 2. `writeNum(number)` : 인자값에 해당하는 값을 숫자 형태로 출력합니다.