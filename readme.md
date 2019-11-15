# Kuin DLL Sample
Kuinに利用するためのC++でのDLL開発を行うために、型の対応関係がわかりにくかったので、コードにしてみました。

# Build
Visual Studio 2019で作成しています。x64向けにReleaseビルドしたらtest_dll.dllが ./x64/Release/ にできると思います。Kuin側ではこのディレクトリを見るようになっています。違うディレクトリの場合はKuin Editorで変更してください。

main.knを実行するとmain.kn内にあるような結果が出力されるはずです。

# 参照型について
Kuinの参照型データ構造に関して調査を行っています。[data_structure.md](./data_structure.md)に随時結果報告を掲載しています。

# License
くいんちゃんライセンス
