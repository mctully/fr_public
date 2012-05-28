.PHONY: example tags clean default

default: example

example:
		xcodebuild -configuration Debug ARCHS=i386

clean:
		xcodebuild -configuration Debug clean -project example_cube.xcodeproj
		xcodebuild -configuration Release clean -project example_cube.xcodeproj

tags:
		cd ..
		ctags -R
