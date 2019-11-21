# Kuin data structure
Kuinの型ごとのデータ構造を分析したのでその結果です。

## Common spec
| Address | what |
| -- | -- |
| 0x00 - 0x09 | metadata |
| 0x10 - 0x?? | maindata |

## Type ids
typedef enum ETypeId

| Type | id |
| -- | -- |
| TypeId_Int | 0x00 |
| TypeId_Float | 0x01 |
| TypeId_Char | 0x02 |
| TypeId_Bool | 0x03 |
| TypeId_Bit8 | 0x04 |
| TypeId_Bit16 | 0x05 |
| TypeId_Bit32 | 0x06 |
| TypeId_Bit64 | 0x07 |
| TypeId_Func | 0x08 |
| TypeId_Enum | 0x09 |
| TypeId_Array | 0x80 |
| TypeId_List | 0x81 |
| TypeId_Stack | 0x82 |
| TypeId_Queue | 0x83 |
| TypeId_Dict | 0x84 |
| TypeId_Class | 0x85 |

## Types
### 型の対応関係
| Kuinic types | C like types |
| -- | -- |
| Int | signed long long |
| Float | double |
| Char | unsigned char |
| Bool | unsigned char |
| Bit8 | unsigned char |
| Bit16 | unsigned short |
| Bit32 | unsigned int |
| Bit64 | unsigned long long |

### 特別な処理を必要としない型
値型は特に処理を必要としません

 - Int
 - Float
 - Char
 - Bool
 - Bit8
 - Bit16
 - Bit32
 - Bit64

### 処理が必要な型
参照型は特別な処理が必要です

| x | Str([]char) | List |
| -- | -- | -- |
| length | 0x10 + len + 1 | 0x28 |

| Address | Str([]char) | List |
| -- | -- | -- |
| 0x00 | DefaultRefCntFunc(8byte) | DefaultRefCntFunc(8byte) | 
| 0x01 | : | : |
| 0x02 | : | : |
| 0x03 | : | : |
| 0x04 | : | : |
| 0x05 | : | : |
| 0x06 | : | : |
| 0x07 | : | : |
| 0x08 | len(8byte) | len(8byte) |
| 0x09 | : | : |
| 0x0a | : | : |
| 0x0b | : | : |
| 0x0c | : | : |
| 0x0d | : | : |
| 0x0e | : | : |
| 0x0f | : | : |
| 0x10 | Char | 0(8byte) |
| 0x11 | Char | : |
| 0x12 | Char | : |
| 0x13 | Char | : |
| 0x14 | Char | : |
| 0x15 | Char | : |
| 0x16 | Char | : |
| 0x17 | Char | : |
| 0x18 | Char | 0(8byte) |
| 0x19 | Char | : |
| 0x1a | Char | : |
| 0x1b | Char | : |
| 0x1c | Char | : |
| 0x1d | Char | : |
| 0x1e | Char | : |
| 0x1f | Char | : |
| 0x20 | Char | 0(8byte) |
| 0x21 | Char | : |
| 0x22 | Char | : |
| 0x23 | Char | : |
| 0x24 | Char | : |
| 0x25 | Char | : |
| 0x26 | Char | : |
| 0x27 | Char | : |
| (0x10 + len) | : | |
| (0x10 + len + 1) | \0 | |

## Listに関する詳細調査
 - 0x10のポインタ（*0x10）のアドレスにある値 == 先頭要素のポインタのアドレス
 - 0x18のポインタ（*0x18）のアドレスにある値 == 末尾要素のポインタのアドレス
 - 0x20のポインタ（*0x20）のアドレスにある値 == 現在の要素のポインタのアドレス
 - N + 1番目の要素のポインタのポインタのアドレスにある値 == N番目の要素のポインタのポインタのさすアドレス

### 初めての要素追加
```
要素のポインタのポインタ（自身のひとつ前の要素のポインタのポインタ） = null
先頭要素のポインタのポインタのさすアドレスにある値 = 要素のポインタ
末尾要素のポインタのポインタのさすアドレスにある値 = 要素のポインタ
```

### 二つ目以降の要素の追加のされ方
```
要素のポインタのポインタのさすアドレスにある値 = 末尾要素（自身のひとつ前の要素）のポインタのポインタ
(末尾要素のポインタのポインタのさすアドレス + 0x08) = 要素のポインタ
末尾要素のポインタのポインタのさすアドレス = 要素のポインタ
```

### 要素のデータ構造
その要素の型の構造

## Classに関する詳細調査
KuinにクラスとCppにstructを定義。structはプロパティとして SClass Class; を必ず持つ
プロパティは同じ名前だが型が異なる
メソッドは、Cppではクラスの中になく、別途関数として定義、エクスポートしてKuinで読み込む
クラスを受け渡しするときは型をSClass*にする
SClass*はcommon.hにあって

```
typedef struct SClass
{
	U64 RefCnt;
	void* ClassTable;
} SClass;
```

Cpp側の関数の第一引数は常に SClass* me_ で、これはpythonの self 的なやつ

SClass*をreinterpret_castで任意の型に変換して利用する

現在の状態の内容を加工して新しい自分を返す必要があるときは、Kuin側の第一引数で me2: @Node のようにインスタンスをわたし、Cpp側の第二引数で SClass* me2 で受けて、me_の内容をme2にコピーしつつ加工する。そしてme2をreturn することでKuin側で func (): @Node のように返り値で受け取れる。ただし、このようにKuinの引数で新しいインスタンスを渡すには 関数のDLL指定で [test.dll, myfuncname, _make_instance] のように三つ目に _make_instanceを指定する必要がある。
