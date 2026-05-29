*This project has been created as part of the 42 curriculum by atajima, syokota.*

# push_swap

## Description

`push_swap` は、2つのスタック `a` と `b`、そして限られた命令だけを使って
整数列を昇順に並べ替える 42 のアルゴリズム課題です。

プログラムは、コマンドライン引数として初期状態のスタック `a` を受け取り、
それをソートするための Push_swap 命令列を標準出力に表示します。出力された
命令を順番に実行すると、スタック `a` は昇順にソートされ、スタック `b` は空に
なります。

この課題での計算量は、一般的な配列ソートの内部処理ではなく、生成される
Push_swap 命令数を基準に考えます。

## Contributors

- `atajima`: スタック操作、引数パース、ソート戦略、ベンチマーク出力、テスト、
  ドキュメント作成。
- `syokota`: プロジェクト初期設定および実装サポート。

評価時には、両メンバーがプロジェクト全体の実装とアルゴリズムを説明できる必要が
あります。

## Instructions

### Build

```sh
make
```

`push_swap` バイナリを生成します。コンパイルには `cc`、`-Wall -Wextra -Werror`
を使用し、ローカルの `libft` をリンクします。

### Clean

```sh
make clean
make fclean
make re
```

### Run

```sh
./push_swap 2 1 3 6 5 8
```

出力例:

```text
sa
pb
ra
pa
```

実際の出力は、入力順や選択した戦略によって変わります。通常モードでは、標準出力に
命令だけを1行ずつ表示します。

### Strategy Flags

デフォルトでは adaptive 戦略が使われます。

```sh
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 4 67 3 87 23
./push_swap --adaptive 4 67 3 87 23
```

使用できるフラグ:

- `--simple`: `O(n^2)` の simple 戦略を強制します。
- `--medium`: `O(n√n)` の medium 戦略を強制します。
- `--complex`: `O(n log n)` の complex 戦略を強制します。
- `--adaptive`: disorder をもとに内部戦略を選択します。

### Benchmark Mode

```sh
./push_swap --bench --adaptive 4 67 3 87 23
```

`--bench` を付けると、命令列は通常通り標準出力に表示され、ベンチマーク情報は
標準エラーに表示されます。

表示される情報:

- disorder の割合
- 使用された戦略と計算量
- 総命令数
- 各命令ごとの実行回数

ベンチマーク情報だけを見たい場合:

```sh
./push_swap --bench 4 67 3 87 23 > /dev/null
```

付属 checker で確認する場合:

```sh
ARG="4 67 3 87 23"
./push_swap --complex $ARG | ./checker_linux $ARG
```

### Error Handling

不正な入力では、標準エラーに `Error` と改行を表示します。

例:

```sh
./push_swap --adaptive 0 one 2 3
./push_swap --simple 3 2 3
```

エラー対象には、整数ではない引数、`int` の範囲外の値、重複した値、未知の
オプションフラグなどが含まれます。

## Operations

このプログラムが生成する可能性のある命令は以下です。

- `sa`, `sb`, `ss`: スタック上部の要素を入れ替える。
- `pa`, `pb`: 片方のスタックの先頭要素をもう片方へ push する。
- `ra`, `rb`, `rr`: スタックを上方向に rotate する。
- `rra`, `rrb`, `rrr`: スタックを下方向に reverse rotate する。

## Disorder Metric

ソートを始める前に、プログラムは `0` から `1` の disorder 値を計算します。

disorder は inversion の割合です。すべての要素ペアについて、大きい値が小さい値
より前にある場合、そのペアを「乱れ」として数えます。

```text
disorder = inversion の数 / 全ペア数
```

- `0.0`: すでにソート済み。
- `1.0`: 最も逆順に近い状態。
- `0.0` から `1.0` の間: 部分的にソートされている状態。

この値は adaptive 戦略の選択に使われ、`--bench` モードでも表示されます。

## Algorithm Choices

### Simple Strategy: Selection-Style Extraction, `O(n^2)`

simple 戦略では、スタック `a` の中から最小値を探し、短い方向に rotate して先頭へ
持ってきたあと、`b` に push します。`a` の要素数が2個または3個になったら、その
小さいケースを直接ソートします。最後に `b` の要素をすべて `a` に戻します。

1つずつ最小値を探して取り出すため、最悪の場合は Push_swap 命令数が二次的に増え、
上限は `O(n^2)` になります。小さい入力や、乱れの少ない入力に向いています。


### Medium Strategy: Chunk Sort, `O(n√n)`

medium 戦略では、まず各ノードに rank を割り当てます。その後、rank の範囲を
おおよそ `√n` サイズの chunk に分け、現在の chunk に属する値を `a` から `b` に
push します。それ以外の値は `a` 内で rotate します。

すべての値を `b` に移したあと、`b` の中から最大 rank を探し、短い方向に rotate
して先頭へ持ってきてから `a` に戻します。

chunk サイズを `√n` 程度にすることで、通過回数と rotate 回数のバランスを取り、
Push_swap の命令モデルにおける目標計算量を `O(n√n)` としています。


### Complex Strategy: Binary Radix Sort, `O(n log n)`

complex 戦略では、まず各値に rank を割り当てます。その rank に対して、下位ビット
から順に binary radix sort を行います。

各 bit pass では、対象 bit が `0` の値を `b` に push し、`1` の値は `a` 内で
rotate します。1回の bit pass が終わるたびに、`b` の要素をすべて `a` に戻します。

bit 数は `log2(n)` 程度で、各 pass では `n` 個の要素を処理するため、生成される
命令数の上限は `O(n log n)` です。


### Adaptive Strategy

adaptive 戦略では、ソート前に disorder を測定し、以下の条件で内部戦略を選びます。

- `a->size <= 5` または `disorder < 0.2`: simple 戦略。
- `a->size <= 100` または `disorder < 0.5`: medium 戦略。
- それ以外: complex 戦略。

しきい値の考え方:

- disorder が低い入力では、局所的な修正で済むことが多いため、simple 戦略を使います。
- disorder が中程度の入力では、chunk による分割が命令数のバランスを取りやすいため、
  medium 戦略を使います。
- disorder が高い入力や大きい入力では、安定した上限を持つ radix sort を使います。

`--bench` モードでは、adaptive が内部的に選択した計算量クラスも表示します。

## Project Structure

```text
includes/                 ヘッダーファイル
libft/                    libftライブラリ
srcs/algorithims/         ソートアルゴリズム
srcs/bench/               ベンチマーク出力
srcs/disorder/            disorder 計算
srcs/operations/          Push_swap 操作
srcs/parser/              引数とフラグの解析
srcs/stack/               スタックとノード操作
```

## Resources

- Linux man-pages:
  https://man7.org/linux/man-pages/man3/malloc.3.html
- cppreference: C dynamic memory management:
  https://en.cppreference.com/w/c/memory
- Wolfram MathWorld: Big-O Notation:
  https://mathworld.wolfram.com/Big-ONotation.html
- NIST Dictionary of Algorithms and Data Structures: big-O notation:
- VisuAlgo: Sorting algorithms visualization:
  https://visualgo.net/en/sorting

## AI usage

- simple / medium / complex / adaptive の各ソート戦略の概要
- disorder に応じて戦略を切り替える設計の整理
- C のコンパイルとリンクに関する説明
- ビルドエラーや参照漏れの確認
