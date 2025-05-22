# 🔢 Game 2048

**Tên:** Đỗ Đức Long  
**Mã sinh viên:** 24021550  
**Ngưỡng điểm mong muốn:** 8.0  

## 🎮 Giới thiệu

Đây là phiên bản đơn giản của game 2048 do em tự xây dựng bằng ngôn ngữ C++ và thư viện đồ họa SDL2. Người chơi điều khiển các ô số bằng phím mũi tên, hợp nhất các ô giống nhau để đạt được ô 2048.

---

## 🧠 Lý do bảo vệ ngưỡng điểm 8.0

Dưới đây là các điểm nổi bật thể hiện nỗ lực tự học, tự triển khai và mở rộng tính năng của mình trong quá trình làm game:

### ✅ Tự học – tự làm:
- Tự triển khai hoàn toàn logic trò chơi 2048, bao gồm di chuyển, gộp ô và sinh ô mới.
- Tự xử lý input từ bàn phím để điều khiển game.
- Tự xây dựng vòng lặp game, logic reset, điều kiện thắng/thua.

### ⚙️ Thuật toán đã cài:
- Di chuyển và hợp nhất các ô số theo quy tắc của 2048 (quét từ trái/phải/trên/dưới).
- Phát sinh ô mới tại vị trí ngẫu nhiên sau mỗi lượt đi.
- Kiểm tra điều kiện thắng (tạo được ô 2048) và điều kiện thua (không còn nước đi).

### 🎨 Tính năng đồ họa:
- Dùng SDL2 để vẽ lưới 4x4 với các ô màu khác nhau tùy theo giá trị.
- Hiển thị số trên từng ô bằng font chữ SDL_ttf.
- Highlight khi có ô mới xuất hiện hoặc gộp thành công.

### 🔊 Âm thanh:
- Có nhạc nền lặp xuyên suốt game.
- Âm thanh khi thắng/ thua.

### 💡 Quá trình làm game:
- Tự học SDL2 thông qua các tutorial và video trên youtube.
- Không dùng code mẫu gốc của game 2048 mà đọc qua và viết lại hoàn toàn.

---

## 🌟 Điểm nổi bật

- **Tự xây dựng toàn bộ game từ đầu với SDL2**, không phụ thuộc vào framework hay mã nguồn mẫu.
- **Cài đặt đầy đủ logic gameplay của 2048**, bao gồm phát sinh ô ngẫu nhiên, hợp nhất, kiểm tra thắng/thua.
- **Giao diện tối giản nhưng rõ ràng, hiển thị đẹp nhờ SDL_ttf và xử lý màu sắc.**

---

## 📚 Nguồn tham khảo

- Hướng dẫn SDL2 cơ bản: https://lazyfoo.net/tutorials/SDL/  
- Tutorial viết game 2048 bằng JavaScript (tham khảo logic): https://play2048.co/  
- Nguồn font: https://vi.piliapp.com/cool-text/
- Nguồn âm thanh: https://pixabay.com/

## 🤖 Mức độ sử dụng AI
 
- Dùng AI để sửa lỗi.
- Dùng AI để gợi ý các cú pháp trong SDL2.
- Dùng để tối ưu một số hàm logic.
---
