# UFOSHOOTER
![default](https://user-images.githubusercontent.com/30017323/44370641-0a91f000-a516-11e8-96a8-f1c15e8cf701.png)
# 概要
+ DirectX11とXAudio2を用いてフルスクラッチで開発した3Dシューティングゲームです。また、効果音とBGMの作曲、パーティクルエフェクトの製作も行いました。

## ゲーム内容
+ UFOがフィールド内にあるトマトを奪いに来ます。
+ プレイヤーはトマトが奪われないようにUFOを倒します。
+ UFOを倒すとコンボとスコアが入ります。コンボを繋げるとUFOを倒したときに得られるスコアも増えます。
+ UFOがトマトを奪うと、フィールド外に逃げていきます。この時にUFOを倒すとトマトを守れます。しかし得られるスコアは減ります。
+ ゲーム終了時に残ったトマトの数に応じてスコアにボーナスが付きます。

## 操作方法
+ 移動方法：キーボードのW,A,S,Dキーで移動できます。
+ ショット：マウスの左クリック。
+ 視点変更：マウスを動かすとできます。
+ 一時停止：ゲームプレイ中にキーボードのXキーを押すと一時停止できます。
+ ゲーム終了：キーボードのEscキーを押すとアプリケーションを終了できます。

## 制作環境
+ 使用したコンパイラー：VisualStudio2017(15.7.5)
+ 使用言語：C++17
+ 使用した音楽制作ソフト：Cubase8.5(pro)
+ 使用したパーティクル制作ソフト：Effekseer(1.32)

**利用した外部ライブラリ**
* FBXSDK
* OpenDynamicsEngine 
* Effekseer
* OggVorbis
* DirectXToolKit 
