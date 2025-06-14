# פרויקט SquareMat

פרויקט C++ פשוט למימוש מחלקת `SquareMat` למטריצות ריבועיות של מספרים ממשיים, עם טעינת אופרטורים ובדיקות יחידה.

## מבנה הפרויקט

- `include/SquareMat.hpp`  
  הצהרת מחלקת `SquareMat` והממשק הציבורי שלה (בנאים, אופרטורים וכו').

- `SquareMat.cpp`  
  מימוש המתודות והאופרטורים של `SquareMat`.

- `main.cpp`  
  תוכנית דוגמה אינטראקטיבית להצגת פעולות על מטריצות עם תפריט.

- `test.cpp`  
  בדיקות יחידה עבור `SquareMat` באמצעות מסגרת `doctest`.

- `doctest.h`  
  ספריית בדיקות header-only.

- `Makefile`  
  פקודות בנייה והרצה:
  - `make Main` – קומפילציה והרצת התוכנית הראשית.
  - `make test` – קומפילציה והרצת בדיקות היחידה.
  - `make valgrind` – בדיקת זליגות זיכרון עם valgrind.
  - `make clean` – ניקוי קבצים זמניים.

## תכונות עיקריות

- בנייה, העתקה ומחיקה (RAII)  
- גישה לאיברים עם בדיקת תחום  
- אופרטורים אריתמטיים: `+`, `-`, יחיד `-`, `*` (מטריצה וסקלר), `%` (איבר-איבר וסקלר), `/` (סקלר), `^` (חזקה)  
- הגדלה/הקטנה: `++`, `--` (pre ו-post)  
- טרנספוזה: `~`  
- דטרמינטה: `!`  
- השוואה: `==`, `!=`, `<`, `>`, `<=`, `>=` (השוואת סכום האיברים)  
- אופרטורי השמה משולבים: `+=`, `-=`, `*=`, `/=`, `%=`  
- קלט/פלט בזרמים: `>>`, `<<`  

## בנייה והרצה

```bash
git clone <repo_url>
cd SquareMatProject
make Main       # קומפילציה והרצת הדגמה
make test       # הרצת בדיקות יחידה
make valgrind   # בדיקת זליגות זיכרון
make clean      # ניקוי קבצים
```

## הערות

- אין שימוש במכולות STL; הנתונים מנוהלים במערכים דינמיים.  
- הבדיקות מכסות פעולות חוקיות וזריקת חריגות במצבים בלתי חוקיים.  
- Email: avrahamavitan@gmail.com  
