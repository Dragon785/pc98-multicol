# pc98-multicol

# 概要
PC9801(VM以降) というと4096色中16色しか表示できないというのが通説ですが、小技を使うともっとたくさん色が出せるので試しに書いてみました。

# 実行方法
出来上がったEXEを実行すると、画面上に7ラインの16階調グラデーションバーが表示されます。
黒は共通ですので色数としては7*15+1で106色出ている計算になります。

# コンパイル環境
OpenWatcom 1.9
リアルモードでもDOSエクステンダでも動きますが、付属のMakefileはDOSエクステンダ用です。

# 動作確認環境
Neko Project 21/W x64 Rev.92+FreeDOS(98)
画面→疑似多色パレット再現を有効に
