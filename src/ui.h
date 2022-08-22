#pragma once

namespace arsuhinars
{
	namespace ui
	{
		// ������� ������������ ����������
		void init();

		// ����� ��������� ����������
		void render();

		// ������� ���������� �������� ���������
		void updateSize();

		// ������� ���������� ������� ����� � �������
		void updateText();

		// ���������� ���� ������
		void showScoresPopUp(unsigned int value);

		// ������� ���� ���������
		void showLoseMenu();
		// �������� ���� ���������
		void hideLoseMenu();
	}
}
