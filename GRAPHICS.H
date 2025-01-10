#if (!defined(__GRAPHICS_H__))
#define __GRAPHICS_H__

/// <summary>
/// グラフィックモードを切り替える
/// </summary>
/// <param name="md">
/// 切り替えるグラフィックモード(下記#define参照)
/// </param>
extern void setGraphMode(unsigned char md);

/// <summary>
/// グラフィック表示の有効/無効切り替え
/// </summary>
/// <param name="enbl"> 0:無効 1:有効 </param>
extern void enableGraph(int enbl);

/// <summary>
/// テキスト表示の有効/無効切り替え
/// </summary>
/// <param name="enbl"> 0:無効 1:有効 </param>
extern void enableText(int enbl);

/// <summary>
/// 16色モードを有効にするか
/// </summary>
/// <param name="enbl">
/// 0:無効 1:有効
/// </param>
extern void enable16Col(int enbl);

/// <summary>
/// 16色パレット定義
/// </summary>
/// <param nam="pal">
/// パレット番号(0-15)
/// </param>
/// <param name="r","g","b">
/// RGBカラー(それぞれ0-15)
/// </param>
extern void setPalette(unsigned char pal, unsigned char r, unsigned char g, unsigned char b);


/* SetGraphMode用画面モード定義 */
#define G200_U 0x40 /* (0b01000000) 200ラインVRAM上部 */
#define G200_L 0x80 /* (0b10000000) 200ラインVRAM下部 */
#define G400   0xc0 /* (0b11000000) 400ライン */
#define GCOL   0x00 /* (0b00000000) カラーモード */
#define GMONO  0x20 /* (0b00100000) 白黒モード */
#define GPG1   0x00 /* (0b00000000) ページ１ */
#define GPG2   0x10 /* (0b00010000) ページ２ */

/// <summary>
/// ボーダーカラー変更
/// </summary>
/// <param name="col">
/// 変更したいボーダーカラー
/// </param>
extern void setBorderColor(int col);

#endif
