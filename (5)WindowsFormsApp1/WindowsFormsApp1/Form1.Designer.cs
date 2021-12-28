namespace WindowsFormsApp1
{
    partial class Main_form
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.GLCtrl = new OpenTK.GLControl();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel_x = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_z = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_y = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel_FPS = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox_Diffuse_Lamp = new System.Windows.Forms.TextBox();
            this.label_Diffuse_Lamp = new System.Windows.Forms.Label();
            this.trackBar_Diffuse_Lamp = new System.Windows.Forms.TrackBar();
            this.textBox_Diffuse_Directional = new System.Windows.Forms.TextBox();
            this.textBox_Ambient = new System.Windows.Forms.TextBox();
            this.label_Diffuse_Directional = new System.Windows.Forms.Label();
            this.label_Ambient = new System.Windows.Forms.Label();
            this.checkButton_Polygon_Mode = new System.Windows.Forms.CheckBox();
            this.trackBar_Ambient = new System.Windows.Forms.TrackBar();
            this.trackBar_Diffuse_Directional = new System.Windows.Forms.TrackBar();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.statusStrip.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.tableLayoutPanel.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Diffuse_Lamp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Ambient)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Diffuse_Directional)).BeginInit();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // GLCtrl
            // 
            this.GLCtrl.BackColor = System.Drawing.Color.White;
            this.GLCtrl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GLCtrl.Location = new System.Drawing.Point(3, 3);
            this.GLCtrl.Name = "GLCtrl";
            this.GLCtrl.Size = new System.Drawing.Size(1024, 681);
            this.GLCtrl.TabIndex = 2;
            this.GLCtrl.VSync = false;
            this.GLCtrl.Load += new System.EventHandler(this.GLCtrl_Load);
            this.GLCtrl.Paint += new System.Windows.Forms.PaintEventHandler(this.GLCtrl_Paint);
            this.GLCtrl.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.GLCtrl_KeyPress);
            this.GLCtrl.KeyUp += new System.Windows.Forms.KeyEventHandler(this.GLCtrl_KeyUp);
            this.GLCtrl.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GLCtrl_MouseDown);
            this.GLCtrl.MouseMove += new System.Windows.Forms.MouseEventHandler(this.GLCtrl_MouseMove);
            this.GLCtrl.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GLCtrl_MouseUp);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel_x,
            this.toolStripStatusLabel_z,
            this.toolStripStatusLabel_y,
            this.toolStripStatusLabel_FPS});
            this.statusStrip.Location = new System.Drawing.Point(0, 711);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1246, 22);
            this.statusStrip.TabIndex = 3;
            this.statusStrip.Text = "statusStrip1";
            // 
            // toolStripStatusLabel_x
            // 
            this.toolStripStatusLabel_x.Name = "toolStripStatusLabel_x";
            this.toolStripStatusLabel_x.Size = new System.Drawing.Size(122, 17);
            this.toolStripStatusLabel_x.Text = "toolStripStatusLabel_x";
            // 
            // toolStripStatusLabel_z
            // 
            this.toolStripStatusLabel_z.Name = "toolStripStatusLabel_z";
            this.toolStripStatusLabel_z.Size = new System.Drawing.Size(122, 17);
            this.toolStripStatusLabel_z.Text = "toolStripStatusLabel_z";
            // 
            // toolStripStatusLabel_y
            // 
            this.toolStripStatusLabel_y.Name = "toolStripStatusLabel_y";
            this.toolStripStatusLabel_y.Size = new System.Drawing.Size(123, 17);
            this.toolStripStatusLabel_y.Text = "toolStripStatusLabel_y";
            // 
            // toolStripStatusLabel_FPS
            // 
            this.toolStripStatusLabel_FPS.Name = "toolStripStatusLabel_FPS";
            this.toolStripStatusLabel_FPS.Size = new System.Drawing.Size(136, 17);
            this.toolStripStatusLabel_FPS.Text = "toolStripStatusLabel_FPS";
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(1246, 24);
            this.menuStrip.TabIndex = 4;
            this.menuStrip.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.menuToolStripMenuItem.Text = "Menu";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // tableLayoutPanel
            // 
            this.tableLayoutPanel.AutoSize = true;
            this.tableLayoutPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tableLayoutPanel.ColumnCount = 2;
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 82.74478F));
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 17.25522F));
            this.tableLayoutPanel.Controls.Add(this.tabControl1, 1, 0);
            this.tableLayoutPanel.Controls.Add(this.GLCtrl, 0, 0);
            this.tableLayoutPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel.Name = "tableLayoutPanel";
            this.tableLayoutPanel.RowCount = 1;
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 97.31993F));
            this.tableLayoutPanel.Size = new System.Drawing.Size(1246, 687);
            this.tableLayoutPanel.TabIndex = 5;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(1033, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(210, 681);
            this.tabControl1.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.Ivory;
            this.tabPage1.Controls.Add(this.textBox1);
            this.tabPage1.Controls.Add(this.textBox_Diffuse_Lamp);
            this.tabPage1.Controls.Add(this.label_Diffuse_Lamp);
            this.tabPage1.Controls.Add(this.trackBar_Diffuse_Lamp);
            this.tabPage1.Controls.Add(this.textBox_Diffuse_Directional);
            this.tabPage1.Controls.Add(this.textBox_Ambient);
            this.tabPage1.Controls.Add(this.label_Diffuse_Directional);
            this.tabPage1.Controls.Add(this.label_Ambient);
            this.tabPage1.Controls.Add(this.checkButton_Polygon_Mode);
            this.tabPage1.Controls.Add(this.trackBar_Ambient);
            this.tabPage1.Controls.Add(this.trackBar_Diffuse_Directional);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(202, 655);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(18, 217);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(59, 20);
            this.textBox1.TabIndex = 11;
            // 
            // textBox_Diffuse_Lamp
            // 
            this.textBox_Diffuse_Lamp.Location = new System.Drawing.Point(135, 144);
            this.textBox_Diffuse_Lamp.Name = "textBox_Diffuse_Lamp";
            this.textBox_Diffuse_Lamp.ReadOnly = true;
            this.textBox_Diffuse_Lamp.Size = new System.Drawing.Size(59, 20);
            this.textBox_Diffuse_Lamp.TabIndex = 10;
            this.textBox_Diffuse_Lamp.TabStop = false;
            // 
            // label_Diffuse_Lamp
            // 
            this.label_Diffuse_Lamp.AutoSize = true;
            this.label_Diffuse_Lamp.Location = new System.Drawing.Point(6, 147);
            this.label_Diffuse_Lamp.Name = "label_Diffuse_Lamp";
            this.label_Diffuse_Lamp.Size = new System.Drawing.Size(103, 13);
            this.label_Diffuse_Lamp.TabIndex = 9;
            this.label_Diffuse_Lamp.Text = "Яркость фонарика";
            // 
            // trackBar_Diffuse_Lamp
            // 
            this.trackBar_Diffuse_Lamp.Location = new System.Drawing.Point(6, 166);
            this.trackBar_Diffuse_Lamp.Maximum = 100;
            this.trackBar_Diffuse_Lamp.Name = "trackBar_Diffuse_Lamp";
            this.trackBar_Diffuse_Lamp.Size = new System.Drawing.Size(180, 45);
            this.trackBar_Diffuse_Lamp.TabIndex = 8;
            this.trackBar_Diffuse_Lamp.Scroll += new System.EventHandler(this.trackBar_Diffuse_Lamp_Scroll);
            // 
            // textBox_Diffuse_Directional
            // 
            this.textBox_Diffuse_Directional.Location = new System.Drawing.Point(135, 77);
            this.textBox_Diffuse_Directional.Name = "textBox_Diffuse_Directional";
            this.textBox_Diffuse_Directional.ReadOnly = true;
            this.textBox_Diffuse_Directional.Size = new System.Drawing.Size(59, 20);
            this.textBox_Diffuse_Directional.TabIndex = 7;
            this.textBox_Diffuse_Directional.TabStop = false;
            // 
            // textBox_Ambient
            // 
            this.textBox_Ambient.Location = new System.Drawing.Point(135, 6);
            this.textBox_Ambient.Name = "textBox_Ambient";
            this.textBox_Ambient.ReadOnly = true;
            this.textBox_Ambient.Size = new System.Drawing.Size(59, 20);
            this.textBox_Ambient.TabIndex = 6;
            // 
            // label_Diffuse_Directional
            // 
            this.label_Diffuse_Directional.AutoSize = true;
            this.label_Diffuse_Directional.Location = new System.Drawing.Point(6, 80);
            this.label_Diffuse_Directional.Name = "label_Diffuse_Directional";
            this.label_Diffuse_Directional.Size = new System.Drawing.Size(109, 13);
            this.label_Diffuse_Directional.TabIndex = 5;
            this.label_Diffuse_Directional.Text = "Направленный свет";
            // 
            // label_Ambient
            // 
            this.label_Ambient.AutoSize = true;
            this.label_Ambient.Location = new System.Drawing.Point(6, 9);
            this.label_Ambient.Name = "label_Ambient";
            this.label_Ambient.Size = new System.Drawing.Size(108, 13);
            this.label_Ambient.TabIndex = 4;
            this.label_Ambient.Text = "Яркость окружения";
            // 
            // checkButton_Polygon_Mode
            // 
            this.checkButton_Polygon_Mode.AutoSize = true;
            this.checkButton_Polygon_Mode.Checked = true;
            this.checkButton_Polygon_Mode.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkButton_Polygon_Mode.Location = new System.Drawing.Point(18, 267);
            this.checkButton_Polygon_Mode.Name = "checkButton_Polygon_Mode";
            this.checkButton_Polygon_Mode.Size = new System.Drawing.Size(154, 17);
            this.checkButton_Polygon_Mode.TabIndex = 3;
            this.checkButton_Polygon_Mode.Text = "Отрисовка поверхностей";
            this.checkButton_Polygon_Mode.UseVisualStyleBackColor = true;
            this.checkButton_Polygon_Mode.CheckedChanged += new System.EventHandler(this.checkButton_Polygon_Mode_CheckedChanged);
            // 
            // trackBar_Ambient
            // 
            this.trackBar_Ambient.Location = new System.Drawing.Point(6, 32);
            this.trackBar_Ambient.Maximum = 100;
            this.trackBar_Ambient.Name = "trackBar_Ambient";
            this.trackBar_Ambient.Size = new System.Drawing.Size(180, 45);
            this.trackBar_Ambient.TabIndex = 1;
            this.trackBar_Ambient.Value = 50;
            this.trackBar_Ambient.Scroll += new System.EventHandler(this.trackBar_Ambient_Scroll);
            // 
            // trackBar_Diffuse_Directional
            // 
            this.trackBar_Diffuse_Directional.Location = new System.Drawing.Point(6, 99);
            this.trackBar_Diffuse_Directional.Maximum = 100;
            this.trackBar_Diffuse_Directional.Name = "trackBar_Diffuse_Directional";
            this.trackBar_Diffuse_Directional.Size = new System.Drawing.Size(180, 45);
            this.trackBar_Diffuse_Directional.TabIndex = 0;
            this.trackBar_Diffuse_Directional.Value = 50;
            this.trackBar_Diffuse_Directional.Scroll += new System.EventHandler(this.trackBar_Diffuse_Directional_Scroll);
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.label13);
            this.tabPage2.Controls.Add(this.label14);
            this.tabPage2.Controls.Add(this.label15);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(202, 655);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 3);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(41, 13);
            this.label13.TabIndex = 15;
            this.label13.Text = "label13";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(53, 3);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(41, 13);
            this.label14.TabIndex = 14;
            this.label14.Text = "label14";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(100, 3);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(41, 13);
            this.label15.TabIndex = 13;
            this.label15.Text = "label15";
            // 
            // Main_form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(1246, 733);
            this.Controls.Add(this.tableLayoutPanel);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.menuStrip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip;
            this.Name = "Main_form";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.tableLayoutPanel.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Diffuse_Lamp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Ambient)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_Diffuse_Directional)).EndInit();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private OpenTK.GLControl GLCtrl;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_x;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_z;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_y;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_FPS;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TrackBar trackBar_Ambient;
        private System.Windows.Forms.TrackBar trackBar_Diffuse_Directional;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.CheckBox checkButton_Polygon_Mode;
        private System.Windows.Forms.Label label_Diffuse_Directional;
        private System.Windows.Forms.Label label_Ambient;
        private System.Windows.Forms.TextBox textBox_Diffuse_Directional;
        private System.Windows.Forms.TextBox textBox_Ambient;
        private System.Windows.Forms.TextBox textBox_Diffuse_Lamp;
        private System.Windows.Forms.Label label_Diffuse_Lamp;
        private System.Windows.Forms.TrackBar trackBar_Diffuse_Lamp;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
    }
}

