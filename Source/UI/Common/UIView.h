#pragma once
#include "Rect.h"
#include <DxLib.h>
#include <vector>
#include "../Enum/EnumMouseClickKind.h"

// ���낢���View�̃x�[�X�ƂȂ�View
class UIView
{
public:
	virtual ~UIView()
	{
	}

	///////////// View ///////////////
	// �eView
	UIView* parent = nullptr;
	// �qView�B
	std::vector<UIView*> subViews;
	// View�̐�Έʒu
	Rect originalFrame;
	// View�̐e�Ƃ̑��Έʒu
	Rect relativeFrame;
	//////////////////////////////////

	/////////// View�̐ݒ� ///////////
	// ���[�U�[����̃A�N�V�����ɔ������邩
	bool enabled = true;
	// ���[�U�[�̃^�b�v�ɔ������邩
	bool userInteractionEnabled = true;
	// �\�������邩 (�e��hidden�Ȃ�"�q����hidden" �ł͂Ȃ��\�����Ȃ�
	bool hidden = false;
	//////////////////////////////////

	//////// ���C�A�E�g�̐ݒ� ////////
	// �w�i�F(�f�t�H���g�͔�
	int backgroundColor = GetColor(255, 255, 255);
	// �w�i�F�̓����x (�f�t�H���g�͓����ɂ��Ȃ�
	int backgroundAlpha = 0xFF;
	//////////////////////////////////

	///////// �}�E�X�̏�� ///////////
	// �}�E�X�J�[�\����View�̏�ɂ��邩
	bool isMouseOver = false;
	// �}�E�X�ɃN���b�N����Ă��邩(�E������)
	bool isMouseClicking = false;
	// �}�E�X�N���b�N�̎��
	EnumMouseClickKind mouseClickingKind = EnumMouseClickKindNONE;
	//////////////////////////////////

	///////// �R���X�g���N�^ /////////
	UIView(){}
	UIView(Rect frame);
	//////////////////////////////////

	/// ���t���[�����ɌĂ΂�鏈�� ///
	// �e����Ă΂�鏈��
	void Update();
	//////////////////////////////////

	//////////// ���\�b�h ////////////
	// �q�r���[��ǉ�
	void addSubView(UIView* view);
	//////////////////////////////////

	//////// �C�x���g�Z�b�g //////////
	/// * �}�E�X�J�[�\������ɂ���Ƃ��̃C�x���g
	// �}�E�X�J�[�\������ԍŏ��ɏ�ɏ������
	void setOnMouseOverBeginCallback(void(*beginMouseOverCallback)(UIView*));
	// �}�E�X�J�[�\������ɏ���Ă��鎞
	void setOnMouseOverWhileCallback(void(*whileMouseOverCallback)(UIView*));
	// �}�E�X�J�[�\�����ォ�痣�ꂽ��
	void setOnMouseOverEndCallback(void(*endMouseOverCallback)(UIView*));

	/// * �}�E�X�ɃN���b�N���ꂽ���̃C�x���g
	// �}�E�X�ɃN���b�N���ꂽ��
	void setOnMouseClickBeginCallback(void(*beginMouseClickCallback)(UIView*, EnumMouseClickKind));
	// �}�E�X�ɃN���b�N����Ă��鎞 (�z�[���h)
	void setOnMouseClickWhileCallback(void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind));
	// �}�E�X�̃N���b�N���I�������
	void setOnMouseClickEndCallback(void(*endMouseClickCallback)(UIView*, EnumMouseClickKind));
	//////////////////////////////////
protected:

	// �`��֐�
	virtual void Draw() const;
	void BackDraw() const;

private:
	////// �O�t���[���̏�ԕێ� //////
	bool isMouseOverBeforeFrame = false;
	bool isMouseClickBeforeFrame = false;
	//////////////////////////////////

	/// ���t���[�����ɌĂ΂�鏈�� ///
	// �e�Ƃ̏����X�V����
	void UpdateRelativeParent();
	// �}�E�X����ɂ��邩�`�F�b�N����
	void CheckMouseOver();
	// �}�E�X�ɃN���b�N����Ă��邩�`�F�b�N����
	void CheckMouseClick();
	//////////////////////////////////
	
	// �C�x���g���X�i
	void(*beginMouseOverCallback)(UIView*) = nullptr;
	void(*whileMouseOverCallback)(UIView*) = nullptr;
	void(*endMouseOverCallback)(UIView*) = nullptr;

	void(*beginMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	void(*endMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	//////////////////////////////////
};
