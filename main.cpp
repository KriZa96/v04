#include "nwpwin.h"

class ship : public vsite::nwp::window {
public:
	ship(uint8_t size_x, uint8_t size_y):
		moving_speed_(0), 
		size_x_(size_x), 
		size_y_(size_y) {}

	std::string class_name() override {
		return "STATIC";
	}

	void create_ship(vsite::nwp::window window_) {
		create(window_, WS_CHILD | WS_VISIBLE | SS_CENTER, "X", 0, current_position_.x, current_position_.y, size_x_, size_y_);
		reset_position();
	}

	void set_current_position(POINT position) {
		current_position_ = position;
	}

	void stop_moving() {
		moving_speed_ = 0;
	}

	void set_moving_speed(int moving_speed) {
		moving_speed_ = moving_speed;
	}

	void move(RECT window_size, int key_press) {
		switch (key_press) {
		case VK_UP:
			move_up(window_size);
			break;
		case VK_DOWN:
			move_down(window_size);
			break;
		case VK_LEFT:
			move_left(window_size);
			break;
		case VK_RIGHT:
			move_right(window_size);
			break;
		}
	}
private:
	int moving_speed_;
	POINT current_position_;
	uint8_t size_x_;
	uint8_t size_y_;

	void reset_position() {
		SetWindowPos(*this, 0, current_position_.x, current_position_.y, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER);
	}

	void move_up(RECT window_size) {
		current_position_.y = (
			current_position_.y - moving_speed_ >= window_size.top ?
			current_position_.y - moving_speed_ :
			window_size.bottom
			);
		reset_position();
	}

	void move_down(RECT window_size) {
		current_position_.y = (
			current_position_.y + moving_speed_ <= window_size.bottom ?
			current_position_.y + moving_speed_ :
			window_size.top
			);
		reset_position();
	}

	void move_left(RECT window_size) {
		current_position_.x = (
			current_position_.x - moving_speed_ >= window_size.left ?
			current_position_.x - moving_speed_ :
			window_size.right
			);
		reset_position();
	}

	void move_right(RECT window_size) {
		current_position_.x = (
			current_position_.x + moving_speed_ <= window_size.right ?
			current_position_.x + moving_speed_ :
			window_size.left
			);
		reset_position();
	}
};

class main_window : public vsite::nwp::window
{
protected:
	void on_left_button_down(POINT p) override { 
		ship_.set_current_position(p);
		if (!ship_) {
			ship_.create_ship(*this);
		}	
	}
	void on_key_up(int vk) override {
		if (ship_) ship_.stop_moving();
	}
	void on_key_down(int vk) override {
		if (!ship_) return;

		RECT window_size;
		bool is_window_present = GetClientRect(*this, &window_size);
		if (!is_window_present) return;

		ship_.set_moving_speed(GetKeyState(VK_CONTROL) < 0 ? 10 : 5);
		ship_.move(window_size, vk);
	}
	void on_destroy() override {
		::PostQuitMessage(0);
	}
private:
	ship ship_{10, 20};
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 4");
	return app.run();
}
